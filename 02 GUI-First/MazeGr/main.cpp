#include<bits/stdc++.h>
#include<allegro.h>
using namespace std;

BITMAP *buffer;
BITMAP *wall;
BITMAP *player;
BITMAP *exit_game;

//pos in Graph
int px=30,py=30;

vector<string>maze;
vector<vector<bool> >visited;
string path;

const int dx[]= {0,0,1,-1};
const int dy[]= {1,-1,0,0};//Right,Left,Up,Down
const char dir[]= {'R','L','D','U'};
int w=0;
int score=1000,steps_left=0;

//This works quite good to identify if there is a path, modified to find path
bool dfs_Solve(int x, int y){
    if(maze[x][y]=='S')return true;
    if(maze[x][y]=='#'||visited[x][y]==1)return false;
    visited[x][y]=1;
    for(int i=0;i<4;i++){
        if(x+dx[i]>=0&&x+dx[i]<w&&y+dy[i]>=0&&y+dy[i]<w){
            if(dfs_Solve(x+dx[i],y+dy[i])){
                path+=dir[i];
                steps_left++;
                return true;
            }
        }
    }
    return false;
}

void init_Score(int x, int y){ //Initial Score func
    visited.assign(w,vector<bool>(w,0));//Visited vector
    dfs_Solve(x,y);
    visited.clear();
    path.clear();
    score+=steps_left;
}

void drw_maze(){
    for(int i=0;i<w;i++){//row
        for(int j=0;j<w;j++){//col
            if(maze[i][j]=='#')draw_sprite(buffer,wall,j*30,i*30);
            if(maze[i][j]=='S')draw_sprite(buffer,exit_game,j*30,i*30);
        }
    }
}

int main(){
    ifstream data ("Levels/L2.in", ifstream::in); //From text file
    string rows;
    int ix=1,iy=1;//Begining of maze
    while(data>>rows){
        maze.push_back(rows);
        w++;
    }//Read data
    data.close();
    init_Score(ix,iy);//Beginning score

    allegro_init();//Allegro init
    install_keyboard();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,((w*30)+200),(w*30),0,0); //window size
    //Load bitmaps
    buffer = create_bitmap(w*30,w*30);//w*30
    wall = load_bitmap("wall.bmp",NULL);
    player=load_bitmap("player.bmp",NULL);
    exit_game=load_bitmap("exit.bmp",NULL);

    char m,store;
    string hint;
    while(!key[KEY_ESC]){
        if(!hint.empty()){
            cout<<"HINT -> "<<hint<<endl;
            hint.clear();
        }
        cout<<"Current Score: "<<score<<endl;

        if(key[KEY_DOWN] || key[KEY_S]){  //MOVEMENT
            if((ix+1>=0&&ix+1<w)&&(maze[ix+1][iy]=='.')){
                store=maze[ix][iy];
                maze[ix][iy]=maze[ix+1][iy];
                maze[ix+1][iy]=store;
                ix++;
                px+=30;
                if(score-1<0)score=0;
                else score--;
            }
        }else if(key[KEY_UP] || key[KEY_W]){
            if((ix-1>=0&&ix-1<w)&&(maze[ix-1][iy]=='.')){
                store=maze[ix][iy];
                maze[ix][iy]=maze[ix-1][iy];
                maze[ix-1][iy]=store;
                ix--;
                px-=30;
                if(score-1<0)score=0;
                else score--;
            }
        }else if(key[KEY_LEFT] || key[KEY_A]){
            if((iy-1>=0&&iy-1<w)&&(maze[ix][iy-1]=='.')){
                store=maze[ix][iy];
                maze[ix][iy]=maze[ix][iy-1];
                maze[ix][iy-1]=store;
                iy--;
                py-=30;
                if(score-1<0)score=0;
                else score--;
            }
        }else if(key[KEY_RIGHT] || key[KEY_D]){
            if((iy+1>=0&&iy+1<w)&&(maze[ix][iy+1]=='.')){
                store=maze[ix][iy];
                maze[ix][iy]=maze[ix][iy+1];
                maze[ix][iy+1]=store;
                iy++;
                py+=30;
                if(score-1<0)score=0;
                else score--;
            }
        }else if(key[KEY_H]){
                visited.assign(w,vector<bool>(w,0));//Visited vector
                dfs_Solve(ix,iy);
                visited.clear();//Wipe visited
                hint+=path[path.size()-1];
                path.clear();
                if(score-1<0)score=0;
                else score--;
        }
        clear(buffer);
        drw_maze(); //draw maze
        draw_sprite(buffer, player,py,px); //draw player
        blit(buffer,screen,0,0,0,0,w*30,w*30);//screen
        rest(75);//delay ms
    }
    return 0;
}
END_OF_MAIN();


