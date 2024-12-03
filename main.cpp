#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;  // Fixated width and height for game limits
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // Array for tail
int nTail = 0;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Enum to change direction
eDirection dir;

// Setting up game configs
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// Draw function
void Draw()
{
    system("cls");

    cout << "Score: " << score << endl;

    // Top wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;


    // Side walls, as snake and food are inside this loop also includes snake and food rendering
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(j == 0)
                cout << "#";

            if(i == y && j == x) // When i and j are equal to position of x,y print the head of snake
                cout << "O";
            else if(i == fruitY && j == fruitX) // Same logic with fruit
                cout << "F";
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; k++) // For-loop of tail lenght
                {
                    if(tailX[k] == j && tailY[k] == i) // When i,j are equal to tail x,y print tail
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }

            if(j == width - 1) // Printing second wall
                cout << "#";
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
}

// Input function checks which key is being pressed and changing direction state
void Input()
{
    if(_kbhit())
    {
        char pressedKey = _getch();
        if(pressedKey == 'a' && dir != RIGHT)
            dir = LEFT;
        else if(pressedKey == 'd' && dir != LEFT)
            dir = RIGHT;
        else if(pressedKey == 'w' && dir != DOWN)
            dir = UP;
        else if(pressedKey == 's' && dir != UP)
            dir = DOWN;
    }
}

// Logic function
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0]; // Tail x,y previous position (initialized in first position)
    int prev2X, prev2Y; // Aux variables for swaping in the tail array
    tailX[0] = x;
    tailY[0] = y;

    // Tail array swaping logic, this updates last tail position
    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Moving logic
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // When hitting wall, snake appears on the other side
    if(x >= width) x = 0; else if (x < 0) x = width - 1;
    if(y >= height) y = 0; else if (y < 0) y = height - 1;

    // When x,y touches any position the tail array the game ends
    for(int i = 0; i < nTail; i++)
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Eating fruit logic, and setting new position when it happens
    if(x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

// Game loop
int main()
{
    Setup();
    while( !gameOver )
    {
        Draw();
        Input();
        Logic();
        //Sleep(10);
    }

    return 0;
}
