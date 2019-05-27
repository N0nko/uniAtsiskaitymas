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
void display();
bool makeBlocks();
void launchGame();
void moveBlock(int, int);
void collidable();
bool checkCollision(int, int);
void updateInput();
bool rotateBolck();
void spwanBlock();

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
    cout << "\n\nSpauskite enter\n";
    cin >> a;
    return 0;
}

void gameLoop() //zaidimo variklis
{
    int time = 0;
    launchGame();

    while (!gameover)
    {
        if (kbhit())
        {
            updateInput();
        }

        if (time < GAMESPEED)
        {
            time++;
        }
        else
        {
            spwanBlock();
            time = 0;
        }
    }
}

int menu()
{
    title();

    int select_num = 0;

    std::cin >> select_num;

    switch (select_num)
    {
    case 1:
    case 2:
    case 3:
        break;
    default:
        select_num = 0;
        break;
    }

    return select_num;
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

void launchGame() //pre setupas, nustatomas zaidziamo lango dydis
{
    for (int i = 0; i <= 20; i++)
    {
        for (int j = 0; j <= 11; j++)
        {
            if ((j == 0) || (j == 11) || (i == 20))
            {
                field[i][j] = stage[i][j] = 9;
            }
            else
            {
                field[i][j] = stage[i][j] = 0;
            }
        }
    }

    makeBlocks();

    display();
}

bool makeBlocks()
{
    x = 4;
    y = 0;

    int blockType = rand() % 6;
    //formu paruosimas
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            block[i][j] = 0;
            block[i][j] = block_list[blockType][i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[i][j + 4] = stage[i][j + 4] + block[i][j];

            if (field[i][j + 4] > 1)
            {
                gameover = true;
                return true;
            }
        }
    }
    return false;
}

void moveBlock(int x2, int y2)
{

    //Formos pasalinimas
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= block[i][j];
        }
    }
    //Koordinaciu atnaujinimas
    x = x2;
    y = y2;

    //Priskirti nauja bloka kordinatem
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] += block[i][j];
        }
    }

    display();
}

void collidable()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            stage[i][j] = field[i][j];
        }
    }
}

bool checkCollision(int x2, int y2)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (block[i][j] && stage[y2 + i][x2 + j] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

void updateInput()
{
    char key;

    key = getch();

    switch (key)
    {
    case 'd':
        if (!checkCollision(x + 1, y))
        {
            moveBlock(x + 1, y);
        }
        break;
    case 'a':
        if (!checkCollision(x - 1, y))
        {
            moveBlock(x - 1, y);
        }
        break;
    case 's':
        if (!checkCollision(x, y + 1))
        {
            moveBlock(x, y + 1);
        }
        break;
    case ' ':
        rotateBolck();
    }
}

bool rotateBolck()
{
    std::vector<std::vector<int>> tmp(4, std::vector<int>(4, 0));

    for (int i = 0; i < 4; i++)
    { //Trumpalaikis formos issaugojimas
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = block[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    { //Pasukimas
        for (int j = 0; j < 4; j++)
        {
            block[i][j] = tmp[3 - j][i];
        }
    }

    if (checkCollision(x, y))
    { // stop jeigu uzdengia kita forma
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                block[i][j] = tmp[i][j];
            }
        }
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= tmp[i][j];
            field[y + i][x + j] += block[i][j];
        }
    }

    display();

    return false;
}

void spwanBlock()
{
    if (!checkCollision(x, y + 1))
    {
        moveBlock(x, y + 1);
    }
    else
    {
        collidable();
        makeBlocks();
        display();
    }
}