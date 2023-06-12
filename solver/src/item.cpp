#include "item.hpp"

/** dim < 4 for optimize AStar */
Item::Item(std::string _str, std::string _path, int dim) :
    str(std::move(_str)), path(std::move(_path)), dim(dim)
{
    // min path
    if (dim < 4)
        f = path.size();
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 'a') {
            zero_ind = i;
            continue;
        }
        if (str[i] != ('b' + i)) {
            if (dim < 4) {
                ++f;
                continue;
            }
            int pos = str[i] - 'b';
            f += std::abs(pos/dim - i/dim) + std::abs(pos%dim - i%dim);
        }
    }
}

const std::string& Item::get_str()  const   { return str; }
const std::string& Item::get_path() const   { return path; }
int   Item::get_zero_ind()          const   { return zero_ind; }

bool Item::is_goal() const {
    if (dim < 4)
        return f - path.size() == 0;
    return f == 0;
}

bool Item::operator>(const Item& item) const {
    return f > item.f;
}