#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <conio.h> // Windows only (for getch and kbhit). On Linux, use ncurses instead.

using namespace std;

int px, py, px1, py1, px2, py2;
int x, y, mx, my, score;
enum edirection { STOP = 0, RIGHT, LEFT, UP, DOWN };
edirection dir;
const int width = 20;
const int height = 20;
int flag;
char choice;
int a;

// Clears the screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Short delay
void delay(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void setup() {
    flag = 0;
    x = width / 2;
    y = height / 2;
    mx = rand() % width;
    my = rand() % height;
    score = 0;
    dir = STOP;
}

void draw() {
    clearScreen();

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";

            if (i == y && j == x)
                cout << "C";
            else if (i == my && j == mx)
                cout << "$";
            else if (i == py && j == px)
                cout << "P";
            else if (i == py1 && j == px1)
                cout << "P";
            else if (i == py2 && j == px2)
                cout << "P";
            else
                cout << " ";

            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        }
    }
}

void police() {
    if (score >= 30) {
        px = rand() % width;
        py = rand() % height;
    }
    if (score >= 70) {
        px1 = rand() % width;
        py1 = rand() % height;
    }
    if (score >= 110) {
        px2 = rand() % width;
        py2 = rand() % height;
    }
}

void logic() {
    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    default: break;
    }

    // Collision with wall
    if (x >= width || x < 0 || y >= height || y < 0) {
        clearScreen();
        cout << "\n\n\tGAME OVER!!!\n";
        cout << "\tYou hit the wall.\n";
        cout << "\tTotal Score: " << score << "\n";
        flag = 1;
        return;
    }

    // Collect money
    if (x == mx && y == my) {
        score += 10;
        mx = rand() % width;
        my = rand() % height;
    }

    police();

    // Caught by police
    if ((x == px && y == py) || (x == px1 && y == py1) || (x == px2 && y == py2)) {
        clearScreen();
        cout << "\n\n\tGAME OVER!!!\n";
        cout << "\tYou were caught by the POLICE!\n";
        cout << "\tTotal Score: " << score << "\n";
        flag = 1;
    }
}

void rules() {
    clearScreen();
    cout << "\n\n\t\t* * CHOR POLICE GAME INSTRUCTIONS * *\n\n";
    cout << " -> You are the Chor 'C' who must collect money '$'.\n";
    cout << " -> Avoid the Police 'P' roaming around the grid.\n";
    cout << " -> Use keys to move:\n";
    cout << "      W = Up\n";
    cout << "      A = Left\n";
    cout << "      S = Down\n";
    cout << "      D = Right\n";
    cout << " -> Collecting '$' increases your score.\n";
    cout << " -> Hitting walls or the police ends the game.\n";
    cout << "\nPress any key to return to the menu...";
    _getch();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    do {
        clearScreen();
        cout << "\n\n\t* * CHOR POLICE GAME * *\n";
        cout << "\n\t1) PLAY";
        cout << "\n\t2) INSTRUCTIONS";
        cout << "\n\t3) EXIT\n\n";
        cout << "Enter your choice: ";
        cin >> a;

        if (a == 2) {
            rules();
        } else if (a == 1) {
            do {
                setup();
                while (!flag) {
                    draw();
                    input();
                    logic();
                    delay(150);
                }

                cout << "\n\nDo you want to play again? (Y/N): ";
                cin >> choice;
            } while (choice == 'y' || choice == 'Y');
        } else if (a == 3) {
            flag = 1;
        }
    } while (a != 3);

    cout << "\nThanks for playing!\n";
    return 0;
}
