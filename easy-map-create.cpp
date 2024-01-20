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
            map[i][j] = 70;
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
    cout << endl;
    int iHolder[x+y-2], jHolder[x+y-2];
    while (pathTravel < x+y-2)
    {
        if (path[pathTravel] == 1)
        {
            map[iGo][jGo] = pathNumbers[pathTravel];
            iHolder[pathTravel] = iGo;
            jHolder[pathTravel] = jGo;
            pathTravel ++;
            iGo ++;
        }
        else if (path[pathTravel] == 2)
        {
            map[iGo][jGo] = pathNumbers[pathTravel];
            iHolder[pathTravel] = iGo;
            jHolder[pathTravel] = jGo;
            pathTravel ++;
            jGo ++;
        }
    }
    int otherNumbersCount = x*y - (x+y-2);
    int zeroCount = rand()%4+2;
    vector<int> otherNumbers;
    for (int i = 0; i < zeroCount; i++)
        otherNumbers.push_back(0);
    for (int i = zeroCount; i < otherNumbersCount; i++){
        otherNumbers.push_back(rand()%7-3);
        while (otherNumbers[i] == 0)
            otherNumbers[i] = rand()%7-3;
    }
    random_shuffle(otherNumbers.begin(), otherNumbers.end());
    int otherNumbersCounter = 0;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (map[i][j] == 70)
            {
                map[i][j] = otherNumbers[otherNumbersCounter];
                otherNumbersCounter++;
            } 
        }
    }
    cout << endl;
    map[x-1][y-1] = sum;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            cout << setw(3) << map[i][j] << "  ";
        }
        cout << endl;
    }
}