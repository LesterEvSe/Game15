#ifndef GAME15_SOLVER_HPP
#define GAME15_SOLVER_HPP

#include <string>
#include <vector>
#include "output.hpp"

class Solver {
    int m_size;
    int m_dim;
    std::vector<std::vector<int>> m_field;

    static char get_direction(int row, int col);
    static std::string matrix_to_str(const std::vector<std::vector<int>>& matrix);

    bool solvable();
    void set_solvable();
    void fill_field();

    /** BFS can solve a 3x3 matrix in the minimum number of moves */
    // std::string bfs();
    std::string AStar();

    Solver(const Solver&) = default;
    Solver(Solver&&) = default;

    Solver& operator=(const Solver&) = default;
    Solver& operator=(Solver&&) = default;

public:
    int solve(bool output=true);
    [[nodiscard]] std::vector<std::vector<int>> get_field() const;

    explicit Solver(int m_dimension=4);
    explicit Solver(const std::vector<std::vector<int>>& field) :
            m_dim((int)field.size()),
            m_size(field.size()*field.size()),
            m_field(field) {}
};


#endif //GAME15_SOLVER_HPP
