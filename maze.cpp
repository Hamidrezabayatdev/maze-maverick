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