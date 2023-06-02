#include "output.hpp"

int main() {
    // 12 moves
    std::vector<std::vector<int>> field3 {
            {1, 3, 4},
            {7, 2, 5},
            {8, 6, 0}
    };

    // 50 moves
    std::vector<std::vector<int>> field4 {
            { 7,  5,  0, 10},
            {11,  6,  1,  3},
            {14,  2, 12,  8},
            { 4,  9, 13, 15}
    };

    // 266 moves
    std::vector<std::vector<int>> field5 {
            {13, 17,  9,  7,  1},
            { 2,  6,  3, 11, 10},
            {16, 21, 15,  5, 20},
            { 4,  0, 12, 23, 14},
            {24, 22, 18, 19,  8}
    };

    Solver game = Solver(3);
    game.solve();

//    int min;
//    while (true) {
//        Solver game = Solver();
//        min = game.solve(false);
//        std::cout << min << std::endl;
//        if (min < 100) {
//            game.solve();
//            break;
//        }
//    }

    return 0;
}
