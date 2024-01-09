#include<iostream>
#include<fstream>
#include<vector>
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
    }
    
}