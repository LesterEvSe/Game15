#ifndef GAME15_SOLVER_HPP
#define GAME15_SOLVER_HPP

#include <string>
#include <vector>

class Solver {
    int m_size;
    int m_dimension;
    std::vector<std::vector<int>> m_field;
    std::pair<int, int> m_zero_pos;

    static char get_direction(int row, int col);

    bool solvable();
    void set_solvable();
    void fill_field();
    std::string AStar();

    Solver(const Solver&) = default;
    Solver(Solver&&) = default;

    Solver& operator=(const Solver&) = default;
    Solver& operator=(Solver&&) = default;

public:
    int solve();
    bool is_solved();
    void move(int row, int col);
    [[nodiscard]] std::vector<std::vector<int>> get_field() const;

    explicit Solver(int dimension);
    explicit Solver(const std::vector<std::vector<int>>& field) :
            m_dimension((int)field.size()),
            m_size(field.size()*field.size()),
            m_field(field) {}
};


#endif //GAME15_SOLVER_HPP
