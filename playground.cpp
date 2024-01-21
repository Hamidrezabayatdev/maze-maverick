#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include <algorithm>
#include <random>
#include<ctime>
using namespace std;
void printMap (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map);
void winningState (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map);
int main()
{
    int row, column;
    cin >> row >> column;
    int** map = new int*[row];
    for (int i = 0; i < row; i++)
        map[i] = new int[column];
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cin >> map[i][j];
            if (i == 0 && j == 0)
                cout << "\033[32m" << setw(3) <<  map[i][j] << "\033[0m" << "  ";
            else
                cout << setw(3) <<  map[i][j] << "  ";
        }
        cout << endl;
    }
    vector<int> xHolder;
    vector<int> yHolder;
    vector<char> moves;
    char move, finalMove;
    int x = 0, y = 0;
    xHolder.push_back(x);
    yHolder.push_back(y);
    bool final = false;
    while (final == false)
    {
        cin >> move;
        if (move == 'B')
        {
            if (moves[moves.size()-1] == 'D')
            {
                y --;
                xHolder.pop_back();
                yHolder.pop_back();
                moves.pop_back();
                printMap(row, column, xHolder, yHolder, map);
            }
            else if (moves[moves.size()-1] == 'A')
            {
                y ++;
                xHolder.pop_back();
                yHolder.pop_back();
                moves.pop_back();
                printMap(row, column, xHolder, yHolder, map);
            }
            else if (moves[moves.size()-1] == 'S')
            {
                x --;
                xHolder.pop_back();
                yHolder.pop_back();
                moves.pop_back();
                printMap(row, column, xHolder, yHolder, map);
            }
            else if (moves[moves.size()-1] == 'W')
            {
                x ++;
                xHolder.pop_back();
                yHolder.pop_back();
                moves.pop_back();
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        
        else if (move == 'D')
        {
            if (y == column-1 || (map[x][y+1] == 0))
                continue;
            else
            {
                moves.push_back('D');
                finalMove = 'D';
                y ++;
                xHolder.push_back(x);
                yHolder.push_back(y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'A')
        {
            if (y == 0 || (map[x][y-1] == 0) || moves[moves.size()-1] == 'D')
                continue;
            else
            {
                moves.push_back('A');
                finalMove = 'A';
                y --;
                xHolder.push_back(x);
                yHolder.push_back(y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'S')
        {
            if (x == row-1 || (map[x+1][y] == 0) || moves[moves.size()-1] == 'W')
                continue;
            else
            {
                moves.push_back('S');
                finalMove = 'S';
                x ++;
                xHolder.push_back(x);
                yHolder.push_back(y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'W')
        {
            if (x == 0 || (map[x-1][y] == 0) || moves[moves.size()-1] == 'S')
                continue;
            else
            {
                moves.push_back('W');
                finalMove = 'W';
                x --;
                xHolder.push_back(x);
                yHolder.push_back(y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'E')
        {
            winningState(row, column, xHolder, yHolder, map);
            cout << "Game ended";
        }
        
        // for testing x and y:
        // cout << endl  << "x: " << x << "\t" << "y: " << y << endl;
        // cout << "xHolder: ";
        // for (int k = 0; k < xHolder.size(); k++)
        //     cout << xHolder[k] << "\t";
        // cout << endl << "yHolder: ";
        // for (int k = 0; k < yHolder.size(); k++)
        //     cout << yHolder[k] << "\t";
        // cout << endl << endl;
    }
}
void printMap (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            int temp = 0;
            for (int k = 0; k < xHolder.size(); k++)
            {
                if (i == xHolder[k] && j == yHolder[k])
                    temp++;
            }
                if (temp > 0)
                {
                    cout << "\033[32m" << setw(3) <<  map[i][j] << "\033[0m" << "  ";
                }
                else
                {
                    cout << setw(3) <<  map[i][j] << "  ";
                }
        }
        cout << endl;
    }
}
void winningState (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map)
{
    int sum = 0;
    for (int i = 0; i < xHolder.size(); i++)
        sum += map[xHolder[i]][yHolder[i]];
    if (map[row-1][column-1] == sum)
        cout << "\033[32m" << "You are succeed" << "\033[0m" << endl;
    else
        cout << "\033[31m" << "Mission faild!" << "\033[0m" << endl;
}