#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>

std::vector<std::vector<int>> stage(22, std::vector<int>(13, 0));
std::vector<std::vector<int>> block =
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

std::vector<std::vector<int>> field(22, std::vector<int>(13, 0));
// koordinate
int y = 0;
int x = 4;
bool gameover = false;
int GAMESPEED = 20000;
