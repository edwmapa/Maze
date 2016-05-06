#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

const int dx[]= {0,0,1,-1};
const int dy[]= {1,-1,0,0};//Right,Left,Up,Down
const char dir[]= {'R','L','U','D'};//Right,Left,Up,Down

vector<string>maze(22,string(22,'#'));
vector<vector<bool> >visited(22,vector<bool>(22,0));

void mazeGen(int x,int y){
    srand (time(NULL));

}


int main(){
    //freopen("t.out","w",stdout);
    int ix=1,iy=1;
    mazeGen(ix,iy);
    for(int i=0;i<22;i++){
        cout<<maze[i]<<endl;
    }
}
