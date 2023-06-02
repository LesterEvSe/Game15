#include "output.hpp"

void Output::print_solution(std::vector<std::vector<int>> field, const std::string& path) {
    std::cout << "Start field\n";
    print_mat(field);

    int zrow, zcol;
    for (int row = 0; row < field.size(); ++row)
        for (int col = 0; col < field[row].size(); ++col)
            if (field[row][col] == 0)
                zrow = row, zcol = col;

    for (int i = 0; i < path.size(); ++i) {
        std::cout << "Move " << i+1 << "\n";
        if (path[i] == 'r') {
            std::swap(field[zrow][zcol], field[zrow][zcol + 1]);
            ++zcol;
        } else if (path[i] == 'l') {
            std::swap(field[zrow][zcol], field[zrow][zcol - 1]);
            --zcol;
        } else if (path[i] == 'u') {
            std::swap(field[zrow][zcol], field[zrow - 1][zcol]);
            --zrow;
        } else {
            std::swap(field[zrow][zcol], field[zrow + 1][zcol]);
            ++zrow;
        }
        print_mat(field);
    }
}

void Output::print_mat(const std::vector<std::vector<int>>& field) {
    for (const auto& arr : field) {
        for (int elem : arr) {
            if (elem) {
                std::cout << std::setw(4) << elem;
                continue;
            }
            std::cout << std::setw(4) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}