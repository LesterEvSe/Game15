#include "database.hpp"

#include <QDebug>

Database::Database() :
    m_stats(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString DBName = "../statistics.sqlite";
    m_stats.setDatabaseName(DBName);

    if (!m_stats.open())
        qDebug() << "Failed to connect to database: " << m_stats.lastError().text();

    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='stats';");
    if (!query.next() &&
            !query.exec("CREATE TABLE stats ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "time INTEGER, "
                        "username TEXT);"))
        qDebug() << "Failed to create stats table: " << query.lastError().text();

}

Database* Database::get_instance()
{
    static Database database = Database();
    return &database;
}

void Database::add_time(unsigned int time_sec, const QString &nickname)
{
    QSqlQuery query;
    query.prepare("INSERT INTO stats (time, username) values (:time, :username);");
    query.bindValue(":time", time_sec);
    query.bindValue(":username", nickname);
    query.exec();


    // 1. Create temporary table
    query.exec("CREATE TABLE temp LIKE stats;");

    // 2. Insert sorted data to temporary table
    query.exec("INSERT INTO temp (time, username) "
               "SELECT time, username FROM stats "
               "ORDER BY time ASC;");

    // 3. Delete original table
    query.exec("DROP TABLE stats;");

    // 4. Rename temporary table
    query.exec("ALTER TABLE temp RENAME TO stats;");

    // 5. Apply constraint
    query.exec("DELETE FROM stats WHERE id > 100;");
}

std::vector<std::vector<QString>> Database::get_time_players()
{
    QSqlQuery query("SELECT time, username FROM stats;");
    query.exec();
    std::vector<std::vector<QString>> stats;

    while (query.next())
        stats.emplace_back(std::vector<QString>
                           {query.value(0).toString(),
                            query.value(1).toString()});
    return stats;
}
