#include "database.hpp"

#include <QDebug>

Database::Database() :
    m_stats(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString DBName = "../statistics.sqlite";
    m_stats.setDatabaseName(DBName);

    if (!m_stats.open())
        qDebug() << "Failed to connect to database: " << m_stats.lastError().text();

    // table - for which dimensionality of the field the result
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='stats';");
    if (!query.next() &&
            !query.exec("CREATE TABLE stats ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "dimension INTEGER NOT NULL, "
                        "time INTEGER NOT NULL, "
                        "username TEXT NOT NULL);"))
        qDebug() << "Failed to create stats table: " << query.lastError().text();
}

Database* Database::get_instance()
{
    static Database database = Database();
    return &database;
}

void Database::add_time(int dimension, unsigned int time_sec, const QString &nickname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO stats (dimension, time, username) values (:dim, :time, :username);");
    query.bindValue(":dim", dimension);
    query.bindValue(":time", time_sec);
    query.bindValue(":username", nickname);
    if (!query.exec())
        throw QSqlError(query.lastError().text());

    // 1. Create temp table
    if (!query.exec("CREATE TABLE temp ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "dimension INTEGER NOT NULL, "
                    "time INTEGER NOT NULL, "
                    "username TEXT NOT NULL);"))
        throw QSqlError(query.lastError().text());

    // 2. Insert sorted data to temporary table
    if (!query.exec("INSERT INTO temp (dimension, time, username) "
                    "SELECT dimension, time, username FROM stats "
                    "ORDER BY time ASC;"))
        throw QSqlError(query.lastError().text());

    // 3. Delete original table
    if (!query.exec("DROP TABLE stats;"))
        throw QSqlError(query.lastError().text());

    // 4. Rename temp table
    if (!query.exec("ALTER TABLE temp RENAME TO stats;"))
        throw QSqlError(query.lastError().text());

    // NEED TO FIX!!!
    // For different dimensions, different results,
    // you need a limit of no more than 100 for each,
    // not all at the same time

    // 5. Apply constraint
    if (!query.exec("DELETE FROM stats WHERE id > 100;"))
        throw QSqlError(query.lastError().text());
}


std::vector<std::vector<QString>> Database::get_time_players(int dimension)
{
    QSqlQuery query("SELECT time, username "
                    "FROM stats "
                    "WHERE dimension = :dim;");
    query.bindValue(":dim", dimension);

    if (!query.exec())
        throw QSqlError(query.lastError().text());

    std::vector<std::vector<QString>> stats;
    while (query.next())
        stats.emplace_back(std::vector<QString>
                           {query.value(0).toString(),
                            query.value(1).toString()});
    return stats;
}
