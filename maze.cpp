#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include <algorithm>    
#include <random>
#include<ctime>
#include <dirent.h>
#include <sys/types.h>
using namespace std;
vector<vector<pair<int, int> > > pathscontainer;
void printMap (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map);
bool winningState (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map);
void pushbacks (vector<int>& xHolder, vector<int>& yHolder, vector<char>& moves, char move, int x, int y);
void popbacks (vector<int>& xHolder, vector<int>& yHolder, vector<char>& moves);
bool customSort (int a, int b);
void addHistory (char dt, string globalUsername, string globalMapname, int time1, bool winOrLose);
void showHistory (int mode);
void leaderboard (string username);
void showLeaderboard (int t);
void easyMapCreate (int t);
void playground (int t);
bool usercheck (string username);
bool mapcheck (string name);
bool isIn (vector<pair<int,int> >& mypath , int elementx, int elementy );
void findPath( int x, int y, int len, vector<pair<int, int> >& path, int ROW, int COL, int** map);
bool tekrar (int tmp);
void hardMap (int t);
struct player
{
    string username;
    int wins;
    int time;
};
int main()
{
    cout << "\033[36m" << "Game started" << "\033[0m\n";
    cout << "1. Create a new map\n2. Playground\n3. Solve a maze\n4. History\n5. Leaderboard\n6. Exit\n";
    int mode;
    do
    {
        cin >> mode;
        if (mode == 1)
        {
            cout << "\t1.1 Easy\n\t1.2 Hard\n";
            int level;
            cin >> level;
            if (level == 1)
                easyMapCreate(2);
            else if (level == 2)
                hardMap(2);
        }
        else if (mode == 2)
            playground(2);
        else if (mode == 4)
            showHistory(2);
        else if (mode == 5)
            showLeaderboard(2);
        cout << "\033[36m" << "\nDo you want to do anything else?\n\t1.Yes\n\t2.No" << "\033[0m\n";
        int anyelse;
        cin >> anyelse;
        if (anyelse == 1)
            cout << "1. Create a new map\n2. Playground\n3. Solve a maze\n4. History\n5. Leaderboard\n6. Exit\n";
        else
            break;
    } while (mode != 6);
    cout << "\033[36m" << "Happy to see U:)" << "\033[0m\n";
    exit(0);
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
bool winningState (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map)
{
    int sum = 0;
    for (int i = 0; i < xHolder.size()-1; i++)
        sum += map[xHolder[i]][yHolder[i]];
    if (map[row-1][column-1] == sum && xHolder[xHolder.size()-1] == row-1 && yHolder[yHolder.size()-1] == column-1)
        return true;
    else
        return false;
}
void pushbacks (vector<int>& xHolder, vector<int>& yHolder, vector<char>& moves, char move, int x, int y)
{
    moves.push_back(move);
    xHolder.push_back(x);
    yHolder.push_back(y);
}
void popbacks (vector<int>& xHolder, vector<int>& yHolder, vector<char>& moves)
{
    xHolder.pop_back();
    yHolder.pop_back();
    moves.pop_back();
}