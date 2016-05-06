#include<bits/stdc++.h>
#include<allegro.h>
using namespace std;

BITMAP *buffer;
BITMAP *wall;
BITMAP *background;
BITMAP *player;
BITMAP *exit_game;
BITMAP *fondo1;
BITMAP *fondo2;
BITMAP *fondo3;
BITMAP *cursor;

//pos in Graph
int px=30,py=0;

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
    visited.clear();
    score+=steps_left;
}

void drw_maze(){
    for(int i=0;i<w;i++){//row
        for(int j=0;j<w;j++){//col
            if(maze[i][j]=='#')draw_sprite(buffer,wall,j*30,i*30);
            if(maze[i][j]=='S')draw_sprite(buffer,exit_game,j*30,i*30);
            if(maze[i][j]=='.')draw_sprite(buffer,background,j*30,i*30);
        }
    }
}


void loadMaze(){
//    ifstream data ("Levels/L2.in", ifstream::in); //From text file
    ifstream data ("Levels/t.out", ifstream::in); //From text file
    string rows;
    while(data>>rows){
        maze.push_back(rows);
        w++;
    }//Read data
    data.close();
}


void normalGame(){
    loadMaze();
    int ix=1,iy=0;//Begining of maze
    init_Score(ix,iy);//Beginning score
    //Load bitmaps
    buffer=create_bitmap(860,660);
    fondo1=load_bitmap("Ingame_1.bmp",NULL);
    fondo2=load_bitmap("Ingame_2.bmp",NULL);
    fondo3=load_bitmap("Ingame_3.bmp",NULL);
    wall=load_bitmap("wall.bmp",NULL);
    background=load_bitmap("background.bmp",NULL);
    player=load_bitmap("player.bmp",NULL);
    exit_game=load_bitmap("exit.bmp",NULL);
    cursor=load_bitmap("cursor.bmp",NULL);

    char m,store;
    string hint;
    while(!key[KEY_ESC]){
        if(!hint.empty()){
            cout<<hint[0]<<endl;
            hint.clear();
            rest(500);
        }
        if(key[KEY_DOWN] || key[KEY_S]){  //MOVEMENT
            if((ix+1>=0&&ix+1<w)&&(maze[ix+1][iy]=='.')){
                store=maze[ix][iy];
                maze[ix][iy]=maze[ix+1][iy];
                maze[ix+1][iy]=store;
                ix++;
                px+=30;
                if(score-1<0)score=0;
                else score--;
                rest(90);//delay ms
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
                rest(90);//delay ms
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
                rest(90);//delay ms
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
                rest(90);//delay ms
            }
        }

        clear(buffer);
        //mouse actions
        if(mouse_x > 684 && mouse_x < 835 && mouse_y > 542 && mouse_y < 587){//menu
            blit(fondo2, buffer, 0, 0, 0, 0, 860, 660);
            if ( mouse_b & 1 ){
                px=30,py=0;
                ix=1,iy=0;
                score=1000;
                destroy_bitmap(buffer);
                break;
            }
        }else if(mouse_x > 659 && mouse_x < 857 && mouse_y > 264 && mouse_y < 330){//hint
            blit(fondo3, buffer, 0, 0, 0, 0, 860, 660);
            if ( mouse_b & 1 ){
                visited.assign(w,vector<bool>(w,0));//Visited vector
                dfs_Solve(ix,iy);
                visited.clear();//Wipe visited
                hint+=path[path.size()-1];
                path.clear();
                if(score-1<0)score=0;
                else score--;
                rest(75);
            }
        }else{
            blit(fondo1, buffer, 0, 0, 0, 0, 860, 660);
        }

        drw_maze(); //draw maze
        draw_sprite(buffer, player,py,px); //draw player
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);
        blit(buffer,screen,0,0,0,0,860,660);//screen
        textprintf_ex( screen, font, 660, 333, makecol(0, 0, 255),1, "%d", score);//show score
    }
}
