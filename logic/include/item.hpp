#ifndef GAME15_ITEM_HPP
#define GAME15_ITEM_HPP

#include <string>

class Item
{
private:
    int f{};

    std::string str;
    std::string path;
    int dim;
    int zero_ind;

public:
    explicit Item(std::string _str, std::string _path, int dim);

    [[nodiscard]] const std::string& get_str() const;
    [[nodiscard]] const std::string& get_path() const;
    [[nodiscard]] int get_zero_ind() const;

    [[nodiscard]] bool is_goal() const;
    bool operator>(const Item& item) const;
};


#endif //GAME15_ITEM_HPP
