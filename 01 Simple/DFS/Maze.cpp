#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

vector<string>maze;
vector<vector<bool> >visited;
string path;

const int dx[]= {0,0,1,-1};
const int dy[]= {1,-1,0,0};//Right,Left,Up,Down
const char dir[]= {'R','L','D','U'};
int steps_left=0,score;
int w=0;
//This works quite good to identify if there is a path, modified to find path
bool dfs_Solve(int x, int y){
    if(maze[x][y]=='S')return true;
    if(maze[x][y]=='#'||visited[x][y]==1)return false;
    visited[x][y]=1;
    for(int i=0;i<4;i++){
        if(x+dx[i]>=0&&x+dx[i]<w&&y+dy[i]>=0&&y+dy[i]<w){
            if(dfs_Solve(x+dx[i],y+dy[i])){
                steps_left++;
                path+=dir[i];
                return true;
            }
        }
    }
    return false;
}

void init_Score(int x, int y){
    visited.assign(w,vector<bool>(w,0));//Visited vector
    dfs_Solve(x,y);
    visited.clear();
    path.clear();
    score=steps_left;
}

int main(){
    ifstream data ("Levels/L.in", ifstream::in); //From text file
    string rows;
    int ix=0,iy=1;//Begining of maze
    while(data>>rows){
        maze.push_back(rows);
        w++;
    }//Read data
    data.close();

    init_Score(ix,iy);//initialize score for player
    for(int i=0;i<w;i++)cout<<maze[i]<<endl;//print in data

    char m,store;
    string hint;
    while(maze[ix][iy]!='S'){
        if(!hint.empty()){
            cout<<"HINT -> "<<hint<<endl;
            hint.clear();
        }
        cout<<ix<<" "<<iy<<endl;
        cout<<"Current Score: "<<score<<endl;
        cin>>m;
        switch(m){
            case 'd':
                if((iy+1>=0&&iy+1<w)&&(maze[ix][iy+1]=='.')){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix][iy+1];
                    maze[ix][iy+1]=store;
                    iy++;
                    score--;
                }
                break;
            case 'a':
                if((iy-1>=0&&iy-1<w)&&(maze[ix][iy-1]=='.')){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix][iy-1];
                    maze[ix][iy-1]=store;
                    iy--;
                    score--;
                }
                break;
            case 'w':
                if((ix-1>=0&&ix-1<w)&&(maze[ix-1][iy]=='.')){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix-1][iy];
                    maze[ix-1][iy]=store;
                    ix--;
                    score--;
                }
                break;
            case 's':
                if((ix+1>=0&&ix+1<w)&&(maze[ix+1][iy]=='.')){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix+1][iy];
                    maze[ix+1][iy]=store;
                    ix++;
                    score--;
                }
                break;
            case 'h':
                visited.assign(w,vector<bool>(w,0));//Visited vector
                dfs_Solve(ix,iy);
                visited.clear();//Wipe visited
                hint+=path[path.size()-1];
                path.clear();
                score--;
                break;
        }
        system("cls");
        for(int i=0;i<w;i++)cout<<maze[i]<<endl;//print in data
        cout<<endl;
    }

}


/*
Note:
*Check when E collides with S, break loop, show score

*Score(0 max, negative if):
    -Max when used min steps. Ex, if there are 14 steps, max score will be 0.
    -if uses hint, score--.
    -if extra moves, score-- for each extra move.

*Need to show a score table.
*/


