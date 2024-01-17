#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include <algorithm>
#include <random>
#include<ctime>
using namespace std;
int main(){
    srand(time(0));
    int x, y;
    cout << "Enter row & column:" << endl;
    cin >> x >> y;
    int map[x][y];
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            map[i][j] = 0;
        }
    }
    vector<int> path;
    // 1 = down
    for (int i = 1; i < x; i++)
        path.push_back(1);
    // 2 = right
    for (int i = 1; i < y; i++)
        path.push_back(2);
    random_shuffle(path.begin(), path.end());
    int iGo = 0, jGo = 0, pathTravel = 0;
    int sum = 0;
    vector<int> pathNumbers;
    for (int i = 0; i < x+y-2; i++)
    {
        pathNumbers.push_back(rand()%7-3);
        while (pathNumbers[i] == 0)
            pathNumbers[i] = rand()%7-3;
        sum += pathNumbers[i];
    }
    while (pathTravel < x+y-2)
    {
        if (path[pathTravel] == 1)
        {
            map[iGo][jGo] = pathNumbers[pathTravel];
            pathTravel ++;
            iGo ++;
        }
        else if (path[pathTravel] == 2)
        {
            map[iGo][jGo] = pathNumbers[pathTravel];
            pathTravel ++;
            jGo ++;
        }
    }
    map[x-1][y-1] = sum;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            cout << setw(2) << map[i][j] << "  ";
        }
        cout << endl;
    }
}