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
int main()
{
    int row, column, customOrImport;
    cout << "Enter row & column:" << endl;
            cin >> row >> column;
    cout << "Playground" << endl << "\t 1.Choose from existing maps" << endl << "\t 2.Import my custom map" << endl;
    cin >> customOrImport;
    int** map = new int*[row];
    for (int i = 0; i < row; i++)
        map[i] = new int[column];
    if (customOrImport == 2)
    {
        string address;
        cout << endl << "Enter your map file address (exp. ././maps/mymap.txt): ";
        cin >> address;
        ifstream inputAddress (address);
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
    if (profile == 1)
    {
        cout << "please enter your username: ";
    }
    
    cout << "please enter your username: ";
    string username;
    cin >> username;
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
    int timeBase = time(0), time1, sumTime;
    vector<int> xHolder;
    vector<int> yHolder;
    vector<char> moves;
    moves.push_back('G');
    char move, finalMove;
    int x = 0, y = 0;
    xHolder.push_back(x);
    yHolder.push_back(y);
    bool final = false;
    while (final == false)
    {
        cin >> move;
        time1 = time(0) - timeBase;
        sumTime += time1;
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
            if (y == column-1 || (map[x][y+1] == 0) || moves[moves.size()-1] == 'A')
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
        else if (move == 'T')
        {
            cout << "time = " << time1 << "s" << endl;
        }
        else if (move == 'E')
        {
            if (winningState(row, column, xHolder, yHolder, map) == true)
            {
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
                    cout << "time = " << time1 << "s" << endl << "Game ended" << endl;
            }
        }
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