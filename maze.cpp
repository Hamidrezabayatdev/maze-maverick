#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
#include <random>
#include<ctime>
#include <bits/stdc++.h>
using namespace std;
int main(){
    cout << "1. Create a new map" << endl;
    cout << "   - 1.1 Easy" << endl << "   - 1.2 Hard" << endl;
    string level;
    cin >> level;
    srand(time(0));
    if (level == "Easy")
    {
        int x, y;
        cout << "Enter x & y:" << endl;
        cin >> x >> y;
        int map[x][y];
        int zeroCounter = rand()%4 + 2;
        vector<string> moves;
        for (int i = 1; i < x; i++)
            moves.push_back("Right");
        for (int i = 1; i < y; i++)
            moves.push_back("Down");
        random_shuffle(moves.begin(), moves.end());
        // map[0][0] = rand()%7-3;
        // while (map[0][0] == 0)
        //     map[0][0] = rand()%7-3;
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                map[i][j] = rand()%7-3;
                while (map[i][j] == 0)
                    map[i][j] = rand()%7-3;
            }
        }
        
    }
    
}