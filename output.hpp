#ifndef GAME15_OUTPUT_HPP
#define GAME15_OUTPUT_HPP

#include "solver.hpp"

#include <iostream>
#include <iomanip>

class Output
{
private:
    friend class Solver;
    static void print_solution(std::vector<std::vector<int>> field, const std::string& path);

public:
    static void print_mat(const std::vector<std::vector<int>>& field);
};


#endif //GAME15_OUTPUT_HPP
