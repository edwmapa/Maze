#include<bits/stdc++.h>
#include<windows.h>

using namespace std;
const int MAZE_SIZE = 22;
const int dx[]= {0,0,1,-1};
const int dy[]= {1,-1,0,0};//Right,Left,Up,Down
vector<string>maze(MAZE_SIZE,string(MAZE_SIZE,'#'));
vector<vector<bool> >visited(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));

bool check_nearest(int x,int y){
    int c=0;
    for(int i=0;i<4;i++){
        if(maze[x+dx[i]][y+dy[i]]=='.')c++;
    }
    if(c==1)return true;
    return false;
}

void mazeGen(int x,int y){
    if(visited[x][y]==1)return;
    visited[x][y]=1;
    maze[x][y]='.';
//    for(int i=0;i<MAZE_SIZE;i++){
//        cout<<maze[i]<<endl;
//    }
    //Sleep(100);
    vector<int>m;
    for(int i=0;i<4;i++)m.push_back(i);

    while(!m.empty()){
        int k=rand()%m.size();
        //cout<<k<<endl;
        if(x+dx[m[k]]>0 && x+dx[m[k]]<MAZE_SIZE-1 && y+dy[m[k]]>0 && y+dy[m[k]]<MAZE_SIZE-1){
            if(check_nearest(x+dx[m[k]],y+dy[m[k]])){
                mazeGen(x+dx[m[k]],y+dy[m[k]]);
            }
        }
        m.erase(m.begin()+k);
    }
    return;
}

int main(){
    //freopen("t.out","w",stdout);
    srand (time(NULL));
    int ix=1,iy=1;
    mazeGen(ix,iy);
    for(int i=0;i<MAZE_SIZE;i++){
        cout<<maze[i]<<endl;
    }

//    for(int i=0;i<MAZE_SIZE;i++){
//        for(int j=0;j<MAZE_SIZE;j++){
//            cout<<visited[i][j];
//        }
//        cout<<endl;
//    }
}
