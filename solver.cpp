#include "solver.hpp"
#include "item.hpp"
#include "output.hpp"

#include <unordered_set>    // To memorize paths in the A* algorithm
#include <queue>
#include <random>

std::string Solver::matrix_to_str(const std::vector<std::vector<int>>& matrix) {
    std::string str;
    for (const auto& arr : matrix)
        for (int elem : arr)
            str += static_cast<char>(elem + 'a');
    return std::move(str);
}


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
        if (!m_field[i / m_dim][i % m_dim]) {
            zero_row = i / m_dim;
            continue;
        }

        for (int j = i + 1; j < m_size; ++j)
            if (m_field[i / m_dim][i % m_dim] > m_field[j / m_dim][j % m_dim] &&
                m_field[j / m_dim][j % m_dim])
                ++inversions;
    }

    // if odd num
    if (m_dim % 2)
        return inversions % 2 == 0;
    else
        // If the row with zero is even and the number of inversions is even too OR
        // the both row and number of inversions are odd, then TRUE
        return ((m_dim - zero_row) % 2) ^ (inversions % 2);
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
        m_field[i/m_dim][i%m_dim] = nums[i];
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

    pq.emplace(matrix_to_str(m_field), "", m_dim);
    if (pq.top().is_goal()) return "Already solved";

    // за допомогою move ми рухаємо наш 0 (тобто пусту клітинку у всі 4 напрямки)
    /*
       Починаємо з другого елементу (використовуємо його та попередній елемент)
       Отримуємо [0, -1] змінюємо ряд на 0 клітинок, стовпець на -1 (тобто рух вліво)
       [-1, 0] ряд змінюється на -1, стовпець на 0, отже рух угору
       [0, 1] рух вправо
       [1, 0] рух вниз
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

            int new_zrow = board.get_zero_ind() / m_dim + move[i-1];
            int new_zcol = board.get_zero_ind() % m_dim + move[i];

            // Якщо нові координати виходять за межі поля, то пропустити цю ітерацію
            if (new_zrow < 0 || new_zrow >= m_dim ||
                new_zcol < 0 || new_zcol >= m_dim) continue;

            // змінюємо позицію нашого поля, перетворюючи двомірні координати в одномірні
            std::swap(temp[new_zrow*m_dim + new_zcol], temp[board.get_zero_ind()]);
            if (visited.find(temp) == visited.end()) {
                visited.emplace(temp);
                pq.emplace(temp, board.get_path() + get_direction(move[i - 1], move[i]), m_dim);
            }
        }
    }
}

std::vector<std::vector<int>> Solver::get_field() const {
    return m_field;
}

Solver::Solver(int dimension) :
        m_dim(dimension),
        m_size(dimension * dimension),
        m_field(dimension, std::vector<int>(dimension))
{
    do {
        fill_field();
        set_solvable();
    } while (!solvable());
}

int Solver::solve(bool output) {
    if (!solvable()) {
        Output::print_mat(m_field);
        std::cout << "This position cannot be resolved\n";
        return -1;
    }
    if (m_dim < 2 || m_dim > 5) {
        std::cout << "Can't solve\n";
        return -1;
    }

    std::string path = AStar();
    if (path == "Already solved") {
        Output::print_mat(m_field);
        std::cout << path << std::endl;
        return 0;
    }

    if (output)
        Output::print_solution(m_field, path);
    return path.size();
}