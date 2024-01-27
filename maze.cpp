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
bool customsort (player& a, player& b)
{
    if (a.wins != b.wins)
        return a.wins > b.wins;
    else
        return a.time < b.time;

}
void addHistory (char* dt, string globalUsername, string globalMapname, int time1, bool winOrLose)
{
    ofstream history ("states/history.txt", ios::app);
    history << "date & time: " << dt << "\n Username: " << globalUsername << "\n Map: " << globalMapname << "\n Time spent: " << time1 << "s";
    if (winOrLose == true)
        history << "\033[32m" << "\n Result: Win!" << "\033[0m\n";
    else
        history << "\033[31m" << "\n Result: Lose!" << "\033[0m\n";
    history << "-----------------------------------------\n\n";
}
void showHistory (int t)
{
    ifstream showHistory ("states/history.txt");
    string lineHistory;
    while (getline(showHistory, lineHistory))
        cout << lineHistory << endl;
}
void leaderboard (vector<player>& players)
{
    ofstream leader ("states/leaderboard.txt");
    sort (players.begin(), players.end(), customsort);
    if (players.size() >= 3)
    {
        for (int i = 0; i < 3; i++)
            leader << i+1 << ". " << players[i].username << " with " << players[i].wins << " wins in " << players[i].time << "s\n";
    }
    else
        for (int i = 0; i < players.size(); i++)
            leader << i+1 << ". " << players[i].username << " with " << players[i].wins << " wins in " << players[i].time << "s\n";
}
void showLeaderboard (int t)
{
    cout << "\033[36m" << "Leaderboard:" << "\033[0m\n";
    ifstream showLeaderboard ("states/leaderboard.txt");
    string lineLeaderboard;
    while (getline(showLeaderboard, lineLeaderboard))
        cout << lineLeaderboard << endl;
}
void playground (int t)
{
    cout << "Playground" << endl;
    int row, column, customOrImport;
    cout << "Enter row: ";
    cin >> row;
    cout << "Enter column: ";
    cin >> column;
    cout << "\t 1.Choose from existing maps" << endl << "\t 2.Import my custom map" << endl;
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
        cout << "\033[36m" << "Do you want to save your map in this game?\n\t1.Yes\n\t2.No" << "\033[0m\n";
        int mapSave;
        cin >> mapSave;
        if (mapSave == 1)
        {
            ofstream importedSave ("maps/" +name+ ".txt");
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                    importedSave << map[i][j];
            }
        }
    }
    else if (customOrImport == 1)
    {
        ifstream mapList ("maps/maps.txt");
        string mapListName;
        while (mapList >> mapListName)
            cout << mapListName << endl;
        cout << endl << "Enter your map Name (exp. Map1): ";
        string name;
        cin >> name;
        while (mapcheck(name) == false)
        {
            cout << "\033[31m" << "Map not found!\nPlease enter an existing map" << "\033[0m\n";
            cin >> name;
        }
        globalMapname = name;
        ifstream inputName ("maps/" +name+ ".txt");
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
                inputName >> map[i][j];
        }
    }
    else
    {
        cout << "\033[31m" << "Invalid input, please start again" << "\033[0m" << endl;
        exit(0);
    }
    cout << "do you have a profile in this game?" << "\n\t 1.Yes \n\t 2.No\n";
    int profile;
    cin >> profile;
    string globalUsername;
    int allGames = 0, wins = 0, finalWinTime = 0, allTime = 0;
    if (profile == 1)
    {
        ifstream userList ("users/users.txt");
        string userListName;
        while (userList >> userListName)
            cout << userListName << endl;
        cout << "please enter your username: ";
        string username;
        cin >> username;
        while (usercheck(username) == false)
        {
            cout << "\033[31m" << "User not found!\nPlease enter an existing User" << "\033[0m\n";
            cin >> username;
        }
        globalUsername = username;
        ifstream user ("users/" +username+ ".txt");
        user >> allGames >> wins >> finalWinTime >> allTime;
    }
    else
    {
    cout << "please enter your username (\033[31mdo not enter 'users'\033[0m): ";
    string username;
    cin >> username;
    globalUsername = username;
    ofstream firstUser ("users/" +username+ ".txt");
    firstUser << "0" << " " << "0" << " " << "0" << " " << "0" << endl;
    ofstream userForAllUsersFile ("users/users.txt", ios::app);
    userForAllUsersFile << username << " ";
    }
    ofstream user ("users/" +globalUsername+ ".txt");
    vector<player> players;
    player st;
    int timeBase = time(0), time1, sumTime;
    cout << "\033[36m" << "Valid inputs:\n\tW for up\n\tS for down\n\tA for left\n\tD for right\n\tB for back\n\tT for time\n\tE for end or give up!\nL for movelist" << "\033[0m\n\n";
    cout << "\033[33m" << "Time started" << "\033[0m\n";
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
                cout << "\033[31m" << "You can't go back at the first place" << "\033[0m\n";
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
                else{
                    cout << "\033[31m" << "There is a block on your right side" << "\033[0m\n";
                    continue;
                }
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
            if (y == 0)
                continue;
            else if (map[x][y-1] == 0)
            {
                cout << "\033[31m" << "There is a block on your left side" << "\033[0m\n";
                continue;
            }
            else if (moves[moves.size()-1] == 'D')
            {
                cout << "\033[36m" << "If you want to go backward, press 'B'" << "\033[0m\n";
                continue;
            }
            else
            {
                y --;
                pushbacks (xHolder, yHolder, moves, move, x, y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'S')
        {
            if (x == row-1)
                continue;
            else if (moves[moves.size()-1] == 'W')
            {
                cout << "\033[36m" << "If you want to go backward, press 'B'" << "\033[0m\n";
                continue;
            }

            else if ((map[x+1][y] == 0))
            {
                if (x == row-2 && y == column-1)
                {
                    x ++;
                    pushbacks (xHolder, yHolder, moves, move, x, y);
                    printMap(row, column, xHolder, yHolder, map);
                }
                else
                {
                    cout << "\033[31m" << "There is a block on down there" << "\033[0m\n";
                    continue;
                }
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
            if (x == 0)
                continue;
            else if (map[x-1][y] == 0)
            {
                cout << "\033[31m" << "There is a block on up there" << "\033[0m\n";
                continue;
            }
            else if (moves[moves.size()-1] == 'S')
            {
                cout << "\033[36m" << "If you want to go backward, press 'B'" << "\033[0m\n";
                continue;
            }

            else
            {
                x --;
                pushbacks (xHolder, yHolder, moves, move, x, y);
                printMap(row, column, xHolder, yHolder, map);
            }
        }
        else if (move == 'T')
        {
            cout << "\033[33m" << "time = " << time1 << "s" << "\033[0m\n";
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
                    cout << "\033[33m" << "time = " << time1 << "s" << "\033[0m" << endl << "\033[36m" << "Game ended" << "\033[0m" << endl;
                    break;
                }
            }
        }
        else if (move == 'L')
        {
            cout << "\033[36m" << "Valid inputs:\n\tW for up\n\tS for down\n\tA for left\n\tD for right\n\tB for back\n\tT for time\n\tE for end or give up!" << "\033[0m\n";
        }
        else
        {
            cout << "\033[31m" << "Invalid input, please enter from this list (W , A , S , D , T , E)" << "\033[0m" << endl;
            cout << "\033[36m" << "You can see movelist by pressing L" << "\033[0m\n\n";
            continue;
        }
    }
    ifstream inputForLeaderboard ("users/users.txt");
    string usernameForLeaderboard;
    while (inputForLeaderboard >> usernameForLeaderboard)
    {
        ifstream forStruct ("users/" + usernameForLeaderboard + ".txt");
        int allGamesForLeaderboard, winsForLeaderboard, winTimeForLeaderboard, timeForLeaderboard;
        forStruct >> allGamesForLeaderboard >> winsForLeaderboard >> winTimeForLeaderboard >> timeForLeaderboard;
        st.username = usernameForLeaderboard;
        st.time = timeForLeaderboard;
        st.wins = winsForLeaderboard;
        players.push_back(st);
    }
    leaderboard (players);
}