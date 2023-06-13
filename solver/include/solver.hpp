#ifndef GAME15_SOLVER_HPP
#define GAME15_SOLVER_HPP

#include <string>
#include <vector>

class Solver {
    int m_size;
    int m_dimension;
    std::vector<std::vector<int>> m_field;
    std::pair<int, int> m_zero_pos;

    int m_counter;
    std::string m_solution;

    static char get_direction(int row, int col);

    bool solvable();
    void set_solvable();
    void fill_field();
    std::string AStar();

public:
    void solve();
    bool is_solved();

    std::pair<int, int> next_move();
    void move(int row, int col);
    [[nodiscard]] const std::vector<std::vector<int>>& get_field() const;

    explicit Solver(int dimension);
    explicit Solver(const std::vector<std::vector<int>>& field) :
            m_dimension((int)field.size()),
            m_size(field.size()*field.size()),
            m_field(field) {}
};


#endif //GAME15_SOLVER_HPP
