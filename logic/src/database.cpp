#include "database.hpp"

Database::Database() :
    m_stats(QSqlDatabase::addDatabase("QSQLITE"))
{
    QString DBName = "../statistics.sqlite";
    m_stats.setDatabaseName(DBName);

    if (!m_stats.open())
        qDebug() << "Failed to connect to database: " << m_stats.lastError().text();

    // A semicolon at the end of the query
    // is needed to separate multiple queries.
    // If the query is only 1, it is not necessary
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name='stats';");
    if (!query.next() &&
            !query.exec("CREATE TABLE stats ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "dimension INTEGER NOT NULL, "
                        "time INTEGER NOT NULL, "
                        "username TEXT NOT NULL)"))
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

    // ROW_NUMBER() - Analitical func. Assign an ordinal number to each line
    // OVER (...) - How is the separation performed
    // PARTITION BY - Analog to GROUP BY, only for analytical functions
    query.prepare("DELETE FROM stats "
                  "WHERE id IN ( "
                  "  SELECT id FROM ( "
                  "    SELECT id, "
                  "      ROW_NUMBER() OVER "
                  "      (PARTITION BY dimension ORDER BY time ASC) "
                  "      AS row_number "
                  "    FROM stats "
                  "    WHERE dimension = :dimension "
                  "  ) WHERE row_number > 10 "
                  ") AND dimension = :dimension");

    query.bindValue(":dimension", dimension);
    if (!query.exec())
        throw QSqlError(query.lastError().text());
}


std::vector<std::pair<QString, QString>> Database::get_time_players(int dimension)
{
    /// If we use bindValue, we have to do as it says here,
    /// query("...") is not allowed, there will be an error!!!
    QSqlQuery query;
    query.prepare("SELECT time, username "
                  "FROM stats "
                  "WHERE dimension = :dimension "
                  "ORDER BY time ASC");
    query.bindValue(":dimension", dimension);

    if (!query.exec())
        throw QSqlError(query.lastError().text());

    std::vector<std::pair<QString, QString>> stats;
    while (query.next())
        stats.emplace_back(query.value(0).toString(),
                           query.value(1).toString());
    return stats;
}

