#include "solver.hpp"
#include "item.hpp"

#include <unordered_set>    // To memorize paths in the A* algorithm
#include <queue>
#include <random>

bool Solver::solvable() {
    // example of composing inversions
    /**
       1 8 2
       _ 4 3
       7 6 5

       we have these types of inversions (here 10):
       (8,2) (8,4) (8,3) (8,7) (8,6)
       (8,5) (4,3) (7,6) (7,5) (6,5)
     */

    int inversions{0};
    int zero_row{-1};

    for (int i = 0; i < m_size; ++i) {
        if (!m_field[i / m_dimension][i % m_dimension]) {
            zero_row = i / m_dimension;
            continue;
        }

        for (int j = i + 1; j < m_size; ++j)
            if (m_field[i / m_dimension][i % m_dimension] > m_field[j / m_dimension][j % m_dimension] &&
                m_field[j / m_dimension][j % m_dimension])
                ++inversions;
    }

    // if odd num
    if (m_dimension % 2)
        return inversions % 2 == 0;
    else
        // If the row with zero is even and the number of inversions is even too OR
        // the both row and number of inversions are odd, then TRUE
        return ((m_dimension - zero_row) % 2) ^ (inversions % 2);
}

void Solver::set_solvable() {
    if (solvable()) return;
    std::reverse(m_field.begin(), m_field.end());
}

void Solver::fill_field() {
    // Initialize nums
    std::vector<int> nums(m_size);
    for (int i = 1; i < m_size; ++i)
        nums[i] = i;

    // Shuffle nums
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(nums.begin(), nums.end(), gen);

    // Copy nums to m_field
    for (int i = 0; i < m_size; ++i)
        m_field[i/m_dimension][i%m_dimension] = nums[i];
}

char Solver::get_direction(int row, int col) {
    if (row == -1 && col == 0)
        return 'u'; // up
    else if (row == 0 && col == -1)
        return 'l'; // left
    else if (row == 1 && col == 0)
        return 'd'; // down
    else
        return 'r'; // right
}

std::string Solver::AStar()
{
    std::unordered_set<std::string> visited;
    std::priority_queue<Item, std::vector<Item>, std::greater<>> pq;

    // convert matrix to string
    std::string str;
    for (const auto& arr : m_field)
        for (int elem : arr)
            str += static_cast<char>(elem + 'a');

    pq.emplace(str, "", m_dimension);
    if (pq.top().is_goal()) return "Already solved";

    // With 'move' we move 0 (i.e. empty cell in all 4 directions
    /*
       Start with the second element (use it and the previous element)
       We get [0,-1], change the row to 0 cells, the column to -1 (i.e., move to the left)
       [-1,0] the row changes to -1, the column to 0, so the movement is up
       [0, 1] move to the right
       [1, 0] move down
     */
    static const int move[] {0, -1, 0, 1, 0};
    static const int dirs = 5;
    while (true) {
        Item board = pq.top();
        pq.pop();

        if (board.is_goal())
            return board.get_path();

        for (int i = 1; i < dirs; ++i) {
            std::string temp = board.get_str();

            int new_zrow = board.get_zero_ind() / m_dimension + move[i-1];
            int new_zcol = board.get_zero_ind() % m_dimension + move[i];

            // Якщо нові координати виходять за межі поля, то пропустити цю ітерацію
            if (new_zrow < 0 || new_zrow >= m_dimension ||
                new_zcol < 0 || new_zcol >= m_dimension) continue;

            // змінюємо позицію нашого поля, перетворюючи двомірні координати в одномірні
            std::swap(temp[new_zrow*m_dimension + new_zcol], temp[board.get_zero_ind()]);
            if (visited.find(temp) == visited.end()) {
                visited.emplace(temp);
                pq.emplace(temp, board.get_path() + get_direction(move[i - 1], move[i]), m_dimension);
            }
        }
    }
}


Solver::Solver(int dimension) :
    m_dimension(dimension),
    m_size(dimension * dimension),
    m_field(dimension, std::vector<int>(dimension)),
    m_counter(0)
{
    do {
        fill_field();
        set_solvable();
    } while (!solvable() || is_solved());

    for (int row = 0; row < m_dimension; ++row)
        for (int col = 0; col < m_dimension; ++col)
            if (m_field[row][col] == 0)
                m_zero_pos = {row, col};
}

void Solver::solve()
{
    m_counter = 0;
    if (solvable() && m_dimension >= 2 && m_dimension <= 5);
        m_solution = AStar();
}

bool Solver::is_solved()
{
    int value = 0;
    for (int row = 0; row < m_dimension; ++row)
        for (int col = 0; col < m_dimension; ++col)
            if (++value % m_size != m_field[row][col])
                return false;
    return true;
}

std::pair<int, int> Solver::next_move()
{
    if (m_counter >= m_solution.size())
        return {-1, -1};

    std::pair<int, int> move;
    switch (m_solution[m_counter])
    {
    case 'r':
        std::swap(m_field[m_zero_pos.first][m_zero_pos.second],
                  m_field[m_zero_pos.first][m_zero_pos.second + 1]);
        move = {0, 1};
        break;

    case 'l':
        std::swap(m_field[m_zero_pos.first][m_zero_pos.second],
                  m_field[m_zero_pos.first][m_zero_pos.second - 1]);
        move = {0, -1};
        break;

    case 'u':
        std::swap(m_field[m_zero_pos.first][m_zero_pos.second],
                  m_field[m_zero_pos.first - 1][m_zero_pos.second]);
        move = {-1, 0};
        break;

    case 'd':
        std::swap(m_field[m_zero_pos.first][m_zero_pos.second],
                  m_field[m_zero_pos.first + 1][m_zero_pos.second]);
        move = {1, 0};
        break;
    }

    m_zero_pos.first += move.first;
    m_zero_pos.second += move.second;
    ++m_counter;
    return move;
}

void Solver::move(int row, int col)
{
    std::swap(m_field[row][col], m_field[m_zero_pos.first][m_zero_pos.second]);
    m_zero_pos = {row, col};
}

const std::vector<std::vector<int>>& Solver::get_field() const {
    return m_field;
}
