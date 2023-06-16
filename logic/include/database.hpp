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
    void add_time(unsigned int time_sec, const QString &nickname);
    std::vector<std::vector<QString>> get_time_players();
};

#endif // DATABASE_HPP
