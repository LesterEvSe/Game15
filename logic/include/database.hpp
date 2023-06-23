#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <QtSql>
#include <vector>

class Database
{
private:
    QSqlDatabase m_stats;

    Database(const Database&) = delete;
    Database(Database&&)      = delete;
    Database& operator=(const Database&) = delete;
    Database& operator=(Database&&)      = delete;
    Database();

public:
    static Database* get_instance();
    void add_time(int dimension, unsigned int time_sec, const QString &nickname);
    std::vector<std::pair<QString, QString>> get_time_players(int dimension);
};

#endif // DATABASE_HPP
