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
void printMap (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map);
bool winningState (int row, int column, vector<int> xHolder, vector<int> yHolder, int** map);
void pushbacks (vector<int>& xHolder, vector<int>& yHolder, vector<char>& moves, char move, int x, int y);
void popbacks (vector<int>& xHolder, vector<int>& yHolder, vector<char>& moves);
void playground (int t);
void addHistory (char dt, string globalUsername, string globalMapname, int time1, bool winOrLose);
int main()
{
    playground(2);
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
    if (map[row-1][column-1] == sum)
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
void addHistory (char* dt, string globalUsername, string globalMapname, int time1, bool winOrLose)
{
    ofstream history ("states/history.txt", ios::app);
    history << "date & time: " << dt << "\n Username: " << globalUsername << "\n Map: " << globalMapname << "\n Time spent: " << time1;
    if (winOrLose == true)
        history << "\n Result: Win!\n";
    else
        history << "\n Result: Lose!\n";
    history << "-----------------------------------------\n\n";
}
void playground (int t)
{
    int row, column, customOrImport;
    cout << "Enter row & column:" << endl;
            cin >> row >> column;
    cout << "Playground" << endl << "\t 1.Choose from existing maps" << endl << "\t 2.Import my custom map" << endl;
    cin >> customOrImport;
    int** map = new int*[row];
    for (int i = 0; i < row; i++)
        map[i] = new int[column];
    string globalMapname;
    if (customOrImport == 2)
    {
        string address;
        cout << endl << "Enter your map file address (exp. ././maps/mymap.txt): \n";
        cin >> address;
        ifstream inputAddress (address);
        cout << endl << "Enter your map Name (exp. Map1): ";
        string name;
        cin >> name;
        globalMapname = name;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
                inputAddress >> map[i][j];
        }
    }
    else
    {
        DIR *dr;
        struct dirent *en;
        dr = opendir("maps/"); //open all directory
        if (dr) {
           while ((en = readdir(dr)) != NULL) {
              cout<<" \n"<<en->d_name; //print all directory name
           }
           closedir(dr); //close all directory
        }
        cout << endl << "Enter your map Name (exp. Map1): ";
        string name;
        cin >> name;
        globalMapname = name;
        ifstream inputName ("maps/" +name+ ".txt");
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
                inputName >> map[i][j];
        }
    }
    cout << "do you have a profile in this game?" << "\n\t 1.Yes \n\t 2.No\n";
    int profile;
    cin >> profile;
    string globalUsername;
    int allGames = 0, wins = 0, finalWinTime = 0, allTime = 0;
    if (profile == 1)
    {
        DIR *dr;
        struct dirent *en;
        dr = opendir("users/"); //open all directory
        if (dr) {
           while ((en = readdir(dr)) != NULL) {
              cout<<" \n"<<en->d_name; //print all directory name
           }
           closedir(dr); //close all directory
        }
        cout << "\nplease enter your username: ";
        string username;
        cin >> username;
        globalUsername = username;
        ifstream user ("users/" +username+ ".txt");
        user >> allGames >> wins >> finalWinTime >> allTime;
    }
    else
    {
    cout << "please enter your username: ";
    string username;
    cin >> username;
    globalUsername = username;
    ofstream firstUser ("users/" +username+ ".txt");
    firstUser << "0" << " " << "0" << " " << "0" << " " << "0" << endl;
    }
    ofstream user ("users/" +globalUsername+ ".txt");
    int timeBase = time(0), time1, sumTime;
    cout << "Time started\n";
    time_t now = time(0); // get current dat/time with respect to system  
    char* dt = ctime(&now); // convert it into string
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
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
    moves.push_back('G');
    char move;
    int x = 0, y = 0;
    xHolder.push_back(x);
    yHolder.push_back(y);
    bool final = false;
    bool winOrLose;
    while (final == false)
    {
        cin >> move;
        time1 = time(0) - timeBase;
        sumTime += time1;
        if (move == 'B')
        {
            if (moves[moves.size()-1] == 'G')
            {
                cout << "You can't go back at the first place\n";
                continue;
            }
            else if (moves[moves.size()-1] == 'D')
            {
                y --;
                popbacks (xHolder, yHolder, moves);
                printMap(row, column, xHolder, yHolder, map);
            }
            else if (moves[moves.size()-1] == 'A')
            {
                y ++;
                popbacks (xHolder, yHolder, moves);
                printMap(row, column, xHolder, yHolder, map);
            }
            else if (moves[moves.size()-1] == 'S')
            {
                x --;
                popbacks (xHolder, yHolder, moves);
                printMap(row, column, xHolder, yHolder, map);
            }
            else if (moves[moves.size()-1] == 'W')
            {
                x ++;
                popbacks (xHolder, yHolder, moves);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        
        else if (move == 'D')
        {
            if (y == column-1 || moves[moves.size()-1] == 'A')
                continue;
            else if ((map[x][y+1] == 0))
            {
                if (x == row-1 && y == column-2)
                {
                    y ++;
                    pushbacks (xHolder, yHolder, moves, move, x, y);
                    printMap(row, column, xHolder, yHolder, map);
                }
                else
                    continue;
            }
            else
            {
                y ++;
                pushbacks (xHolder, yHolder, moves, move, x, y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'A')
        {
            if (y == 0 || (map[x][y-1] == 0) || moves[moves.size()-1] == 'D')
                continue;
            else
            {
                y --;
                pushbacks (xHolder, yHolder, moves, move, x, y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'S')
        {
            if (x == row-1 || moves[moves.size()-1] == 'W')
                continue;
            else if ((map[x+1][y] == 0))
            {
                if (x == row-2 && y == column-1)
                {
                    x ++;
                    pushbacks (xHolder, yHolder, moves, move, x, y);
                    printMap(row, column, xHolder, yHolder, map);
                }
                else
                    continue;
            }
            else
            {
                x ++;
                pushbacks (xHolder, yHolder, moves, move, x, y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'W')
        {
            if (x == 0 || (map[x-1][y] == 0) || moves[moves.size()-1] == 'S')
                continue;
            else
            {
                x --;
                pushbacks (xHolder, yHolder, moves, move, x, y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'T')
        {
            cout << "time = " << time1 << "s" << endl;
        }
        else if (move == 'E')
        {
            if (winningState(row, column, xHolder, yHolder, map) == true)
            {
                winOrLose = true;
                allGames ++;
                wins ++;
                finalWinTime = time1;
                allTime += time1;
                addHistory (dt, globalUsername, globalMapname, time1, winOrLose);
                user << allGames << " " << wins << " " << finalWinTime << " " << allTime << "\n\n";
                user << "All games: " << allGames << "\nWins: " << wins << "\nFinal win time: " << finalWinTime << "s" << "\nAll games time: " << allTime << "s" << endl;
                cout << "\033[32m" << "You are succeed" << "\033[0m" << endl << "time = " << time1 << "s" << endl << "Game ended" << endl;
                break;
            }
            else
            {
                cout << "\033[31m" << "Mission faild!" << "\033[0m" << endl;
                cout << "\t 1.Continue" << endl << "\t 2.give up!" << endl;
                int cg;
                cin >> cg;
                if (cg == 1)
                    continue;
                else
                {
                    winOrLose = false;
                    allGames ++;
                    allTime += time1;
                    addHistory (dt, globalUsername, globalMapname, time1, winOrLose);
                    user << allGames << " " << wins << " " << finalWinTime << " " << allTime << "\n\n";
                    user << "All games: " << allGames << "\nWins: " << wins << "\nFinal win time: " << finalWinTime << "s" << "\nAll games time: " << allTime << "s" << endl;
                    cout << "time = " << time1 << "s" << endl << "Game ended" << endl;
                    break;
                }
            }
        }
    }
}