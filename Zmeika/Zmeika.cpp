#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20, height = 20;
int nTail, eaten, score, x, y, fruit_x, fruit_y, tailX[100], tailY[100];
enum edirect { stop = 0, LEFT, RIGHT, up, down };
edirect dir;

void setup()
{
    srand(100);
    gameOver = false;
    dir = stop;
    x = width / 2 - 1;
    y = height / 2 - 1;
    srand(time(0));
    fruit_x = rand() % (width - 2) + 2;
    fruit_y = rand() % (height - 2) + 2;
    score = 0;
}

void draw()
{
    //i - координата по y, j - координата по х.
    system("cls");
    for (int j = 1; j <= height; j++)
    {
        for (int i = 1; i <= width; i++)
        {
            //if (i == 1 || i == width || j == 1 || j == height)
            if (i == width || j == height)
            {
                cout << "#";
            }
            else if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruit_y && j == fruit_x)
            {
                cout << "+";
            }
            else
            {
                //Рисуем хвостик змейки
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailY[k] == i && tailX[k] == j)
                    {
                        print = true;
                        cout << "8";
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    cout << "Счет : " << score << endl;
    cout << "Сьедено фруктов : " << eaten << endl;
    cout << "\nИспользуйте WASD для перемещения. Q - Выйти из игры." << endl;
    cout << "Если змейка не двигается переключите раскладку клавиатуры на английскую." << endl;
}

void input()
{

    switch (_getch())
    {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = up;
        break;
    case 's':
        dir = down;
        break;
    case 72:
        dir = up;
        break;
    case 80:
        dir = down;
        break;
    case 77:
        dir = RIGHT;
        break;
    case 75:
        dir = LEFT;
        break;
    case 'q': // Выход из игры.
        gameOver = true;
        break;
    }
}

void logic()
{
    // x - вверх вниз, y - лево право
    int prevY = tailY[0];
    int prevX = tailX[0];
    int prev2Y, prev2X;
    tailY[0] = y;
    tailX[0] = x;
    for (int i = 1; i < nTail; i++)
    {
        prev2Y = tailY[i];
        prev2X = tailX[i];
        tailY[i] = prevY;
        tailX[i] = prevX;
        prevY = prev2Y;
        prevX = prev2X;
    }
    switch (dir)
    {
    case LEFT:
        y--;
        break;
    case RIGHT:
        y++;
        break;
    case up:
        x--;
        break;
    case down:
        x++;
        break;
    }

    //если змейка вышла в стенку - она умрет
    if (x > width - 1 || y > height - 1)
    {
        gameOver = true;
        cout << "Змейка ударилась об стену!" << endl;
    }

    // Перемещение через стенки.
    /*if (x >= width - 0)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 0;*/

    //Гейм овер когда змейка сьедает себя
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
            cout << "Змейка сьела себя!" << endl;
        }
    }

    //Накопление очков
    if (x == fruit_x && y == fruit_y)
    {
        score += 50;
        eaten += 1;

        fruit_x = rand() % (width - 2) + 2;
        fruit_y = rand() % (height - 2) + 2; //проверяет координаты змеи и только потом отрисовывает фрукт
        nTail++;
        cout << " +50 " << endl;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    system("color A0");
    setup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
    }
    return 0;
}