#include "Ennemi.hpp"
using namespace std;

void Ennemi::moveRandomely(std::mt19937 &G) {
    std::uniform_real_distribution<double> X(-10, 10);
    double new_x = get_position_x() + X(G);
    set_position_x(new_x);
}