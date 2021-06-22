#include <iostream>
#include <list>
#include <ctime>
#include <math.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <random>
#include <vector>
using namespace std;

const int SIZE = 2000;
const int SAMPLE_SIZE = 100;
default_random_engine generator;
uniform_real_distribution<double> distribution(0.0,1.0);

void check_neighbour(int& cnt, double p, int x, int y, bool visited[SIZE][SIZE], list<vector<int>>& queue){
    if (!visited[x][y]){
        double randnum = distribution(generator);
        if (p > randnum){
            visited[x][y] = true;
            vector<int> next = {x, y};
            cnt++;
            queue.push_back(next);
        }
    }
}

int BFS1(double p)
{
    static bool visited[SIZE][SIZE];
    for(int i = 0; i < SIZE; i++){
        for (int j=0; j < SIZE; j++){
        visited[i][j] = false;
        }
    }
    list<vector<int>> queue;
    visited[SIZE/2][SIZE/2] = true;
    vector<int> start = {SIZE/2,SIZE/2};
    queue.push_back(start);

    int cnt = 1;
    double randnum;
    while(!queue.empty() && cnt <50000)
    {
        vector<int> s = queue.front();
        queue.pop_front();
        if (max(s[0], s[1]) >= SIZE-1 || min(s[0], s[1]) <= 0){
            cout << "WARNING: edge reached. Continuing with another site";
            continue;
        }

        if ((s[0]+s[1])%2==0){
            check_neighbour(cnt,  p, s[0]+1, s[1], visited, queue);
            check_neighbour(cnt, p, s[0]-1, s[1], visited, queue);
        }
        else{
            check_neighbour(cnt,  p, s[0], s[1]-1, visited, queue);
            check_neighbour(cnt, p, s[0], s[1]+1, visited, queue);
        }
    }
    return cnt;
}

int BFS2(double p)
{
    static bool visited[SIZE][SIZE];
    for(int i = 0; i < SIZE; i++){
        for (int j=0; j < SIZE; j++){
        visited[i][j] = false;
        }
    }
    list<vector<int>> queue;
    visited[0][0] = true;
    vector<int> start = {0,0};
    queue.push_back(start);

    int cnt = 1;
    while(!queue.empty() && cnt <50000)
    {
        vector<int> s = queue.front();
        queue.pop_front();
        if (max(s[0], s[1]) >= SIZE-1){
            cout << "WARNING: edge reached. Continuing with another site";
            continue;
        }

        check_neighbour(cnt,  p, s[0]+1, s[1], visited, queue);
        check_neighbour(cnt, p, s[0], s[1]+1, visited, queue);
    }
    return cnt;
}



int main(){
ofstream myfile;
myfile.open ("07395.txt");

for (int i=0; i<10000; i++){
    if (i%100 == 0){
        cout << i/100 << "\n";
    }
    double p = 0.7395;
    int result = BFS1(p);
    myfile << result << "\n";
    }

}


