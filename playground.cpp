#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include <algorithm>
#include <random>
#include<ctime>
using namespace std;
// void printMap (int row, int column, vector<int> xHolder, vector<int> yHolder, int map[row][column]);
int main()
{
    int row, column;
    cin >> row >> column;
    int map[row][column];
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
            if (finalMove == 'D')
            {
                y --;
                xHolder.pop_back();
                yHolder.pop_back();
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
            else if (finalMove == 'A')
            {
                y ++;
                xHolder.pop_back();
                yHolder.pop_back();
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
            else if (finalMove == 'S')
            {
                x --;
                xHolder.pop_back();
                yHolder.pop_back();
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
            else if (finalMove == 'W')
            {
                x ++;
                xHolder.pop_back();
                yHolder.pop_back();
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
        }
        
        else if (move == 'D')
        {
            if (y == column-1 || (map[x][y+1] == 0) || finalMove == 'A')
                continue;
            else
            {
                finalMove = 'D';
                y ++;
                xHolder.push_back(x);
                yHolder.push_back(y);
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
        }
        else if (move == 'A')
        {
            if (y == 0 || (map[x][y-1] == 0) || finalMove == 'D')
                continue;
            else
            {
                finalMove = 'A';
                y --;
                xHolder.push_back(x);
                yHolder.push_back(y);
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
        }
        else if (move == 'S')
        {
            if (x == row-1 || (map[x+1][y] == 0) || finalMove == 'W')
                continue;
            else
            {
                finalMove = 'S';
                x ++;
                xHolder.push_back(x);
                yHolder.push_back(y);
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
        }
        else if (move == 'W')
        {
            if (x == 0 || (map[x-1][y] == 0) || finalMove == 'S')
                continue;
            else
            {
                finalMove = 'W';
                x --;
                xHolder.push_back(x);
                yHolder.push_back(y);
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
        }
        cout << endl  << "x: " << x << "\t" << "y: " << y << endl;
        cout << "xHolder: ";
        for (int k = 0; k < xHolder.size(); k++)
            cout << xHolder[k] << "\t";
        cout << endl << "yHolder: ";
        for (int k = 0; k < yHolder.size(); k++)
            cout << yHolder[k] << "\t";
        cout << endl << endl;
        if (x == row-1 && y == column-1)
            break;
    }
    
}
// void printMap (int row, int column, vector<int> xHolder, vector<int> yHolder, int map[row][column])
// {
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < column; j++)
//         {
//             int temp = 0;
//             for (int k = 0; k < xHolder.size(); k++)
//             {
//                 if (i == xHolder[k] && j == yHolder[k])
//                     temp++;
//             }
//                 if (temp > 0)
//                 {
//                     cout << "\033[32m" << setw(3) <<  map[i][j] << "\033[0m" << "  ";
//                 }
//                 else
//                 {
//                     cout << setw(3) <<  map[i][j] << "  ";
//                 }
//         }
//         cout << endl;
//     }
// }