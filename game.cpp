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
std::vector<std::vector<std::vector<int>>> block_list =
    {
        {{0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}},
        {{0, 0, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}},
        {{0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0}},
        {{0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}},
        {{0, 0, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 1, 0},
         {0, 0, 1, 0}}};

int menu();
int gameOver();
void title();
void gameLoop();

int main()
{
    switch (menu())
    {
    case 1:
        gameLoop();
        break;
    case 2:
        return 0;
    }
    return 0;
}

int gameOver()
{
    using namespace std;

    char a;
    cout << "   _____                         ____                 " << endl;
    cout << "  / ____|                       | __ |                " << endl;
    cout << " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ " << endl;
    cout << " | | |_ |/ _` | '_ ` _ | / _ | | |  | | | / / _ | '__|" << endl;
    cout << " | |__| | (_| | | | | | |  __/ | |__| || V /  __/ |   " << endl;
    cout << " | _____||__,_|_| |_| |_||___| | ____/  |_/ |___|_|   " << endl;
    cout << "                                                      " << endl;
    cout << "\n\nPress any key and enter\n";
    cin >> a;
    return 0;
}

void title()
{
    using namespace std;

    system("cls");

    cout << "#=====================================================#" << endl;

    cout << "  _______   _        _     " << endl;
    cout << " |__   __| | |      (_)    " << endl;
    cout << "    | | ___| |_ _ __ _ ___ " << endl;
    cout << "    | |/ _ | __| '__| / __|" << endl;
    cout << "    | |  __/ |_| |  | |__ |" << endl;
    cout << "    |_||___||__|_|  |_|___/" << endl;
    cout << "                           " << endl;

    cout << "\t<Meniu>" << endl;
    cout << "\t1: Pradeti" << endl;
    cout << "\t2: Iseiti" << endl;

    cout << "#=====================================================#" << endl;
    cout << "Jusu pasirinkimas >> ";
}

void display()
{
    system("cls");

    for (int i = 0; i < 21; i++)  //nusakomas ekrano dydis
    {
        for (int j = 0; j < 12; j++) //nesu tikras kodel neveikia be STD::
        {
            switch (field[i][j])
            {
            case 0:
                std::cout << " " << std::flush; //tustuma 
                break;
            case 9:
                std::cout << "@" << std::flush; //remas
                break;
            default:
                std::cout << "#" << std::flush; //tekstura
                break;
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\n\tA: Kaire\tS: Zemyn\tD: Desine \t Paversti[Space]";

    if (gameover)
    {
        system("cls");
        gameOver();
    }
}