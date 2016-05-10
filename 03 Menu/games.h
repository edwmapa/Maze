#include<bits/stdc++.h>
#include"inputAlleg.h"
using namespace std;

BITMAP *buffer;
BITMAP *wall;
BITMAP *background;
BITMAP *player;
BITMAP *exit_game;
BITMAP *fondo1;
BITMAP *fondo2;
BITMAP *fondo3;

//pos in Graph
int px=30,py=30;

const int MAZE_SIZE = 22;
const int dx[]= {0,0,1,-1};
const int dy[]= {1,-1,0,0};//Right,Left,Up,Down
const char dir[]= {'R','L','D','U'};
int steps_left=0;

using namespace std;
vector<string>maze(MAZE_SIZE,string(MAZE_SIZE,'#'));
vector<vector<bool> >visited(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));
string path;

//MAZE SOLVING DFS
bool dfs_Solve(int x, int y){
    if(maze[x][y]=='S')return true;
    if(maze[x][y]=='#'||visited[x][y]==1)return false;
    visited[x][y]=1;
    for(int i=0;i<4;i++){
        if(x+dx[i]>=0&&x+dx[i]<MAZE_SIZE&&y+dy[i]>=0&&y+dy[i]<MAZE_SIZE){
            if(dfs_Solve(x+dx[i],y+dy[i])){
                path+=dir[i];
                steps_left++;
                return true;
            }
        }
    }
    return false;
}

 //INITIAL SCORE FUNCTION
int init_Score(int x, int y){
    visited.assign(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));//Visited vector
    dfs_Solve(x,y);
    visited.clear();
    path.clear();
    visited.clear();
    return steps_left;
}

//LOAD MAZE ON SCREEN
void loadBmp(){
    //Load bitmaps
    buffer=create_bitmap(860,660);
    fondo1=load_bitmap("Img/Ingame_1.bmp",NULL);
    fondo2=load_bitmap("Img/Ingame_2.bmp",NULL);
    fondo3=load_bitmap("Img/Ingame_3.bmp",NULL);
    wall=load_bitmap("Img/wall.bmp",NULL);
    background=load_bitmap("Img/background.bmp",NULL);
    player=load_bitmap("Img/player.bmp",NULL);
    exit_game=load_bitmap("Img/exit.bmp",NULL);
    return;
}

void drw_maze(){
    for(int i=0;i<MAZE_SIZE;i++){//row
        for(int j=0;j<MAZE_SIZE;j++){//col
            if(maze[i][j]=='#')draw_sprite(buffer,wall,j*30,i*30);
            if(maze[i][j]=='S')draw_sprite(buffer,exit_game,j*30,i*30);
            if(maze[i][j]=='.')draw_sprite(buffer,background,j*30,i*30);
        }
    }
}


//MAZE AUTO-GENERATION
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

void loadMaze(int x,int y){
    srand (time(NULL));
    int ix=1,iy=1;
    mazeGen(ix,iy);
    maze[ix][iy]='E';
    int exit=rand()%MAZE_SIZE;
    while(maze[20][exit]=='#'){
        exit=rand()%MAZE_SIZE;
    }
    maze[20][exit]='S';
    visited.clear();
}

//CLEAN MAZE
void wipe_maze(){
    maze.clear();
    maze.assign(MAZE_SIZE,string(MAZE_SIZE,'#'));
    visited.clear();
    visited.assign(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));
    return;
}


//WIN MESSAGE
string current_time(){//time stamp
    string year,mo,day;
    stringstream sa,sb,sc;
    time_t now = time(0);
    tm *ltm = localtime(&now); //struct
    sa<<(1900+ltm->tm_year);
    year=sa.str();
    sb<<(1+ltm->tm_mon);
    mo=sb.str();
    sc<<ltm->tm_mday;
    day=sc.str();
    return year+"/"+mo+"/"+day;// year/month/day form
}

void win_game(int current_score, bool which_file){
    string choosenFile;
    if(which_file)choosenFile="Scores/arcade_score.sc";//TRUE - 1 - arcade
    else choosenFile="Scores/normal_score.sc"; //FALSE - 0 - normal

    //CREATE DIALOG
    ifstream fin(choosenFile);
    int min_score;
    fin>>min_score;
    if(current_score>=min_score){
        min_score=(which_file)?256:1001;
        stringstream ss;
        ss<<current_score;
        string sco=ss.str();
        if(alert("Su puntaje actual es: ", sco.c_str(), "Desea guardar el puntaje?","&Si", "&No", 's', 'n')==1){//YES OPTION
            vector<int>sc(11,0);//scores
            vector<string>name(11,"");//names
            vector<string>tm(11,"");//time
            for(int i=0;i<10;i++){
                fin>>sc[i]>>name[i]>>tm[i];
                min_score=min(min_score,sc[i]);
            }
            sc[10]=current_score;// have to sort score
            name[10]=input_form();
            tm[10]=current_time();// keep tracking on date

            //sort, keep data asociated with time - Insertion Sort
            for(int i=1;i<11;i++){
                int x=sc[i];
                string keep=tm[i];
                string keep2=name[i];
                int j=i-1;
                while(j>=0 && sc[j]>x){
                    sc[j+1]=sc[j];
                    tm[j+1]=tm[j];
                    name[j+1]=name[j];
                    j=j-1;
                }
                sc[j+1]=x;
                tm[j+1]=keep;
                name[j+1]=keep2;
            }
            ofstream fout(choosenFile);
            fout<<min_score<<endl;
            for(int i=10;i>=1;i--){
                fout<<sc[i]<<" "<<name[i]<<" "<<tm[i]<<endl;
            }
            fout.close();
        }else alert("Su puntaje no fue almacenado","Presione Ok para continuar "," ","&Ok",NULL,'o',0);
    }else{
        alert("GAME OVER!","Presione Ok para continuar"," ","&Ok",NULL,'o',0);
    }
    fin.close();

    //CLEAN MAZE
    px=30,py=30;
    steps_left=0;
    maze.clear();
    maze.assign(MAZE_SIZE,string(MAZE_SIZE,'#'));
    visited.clear();
    visited.assign(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));

    return;
}

//NORMAL GAME OPTION
void normalGame(){
    int ix=1,iy=1;//Begining of maze
    int score=0;
    loadMaze(ix,iy);//createMaze
    score=init_Score(ix,iy)+1000;//Initial score
    loadBmp();//load bitmaps;

    //FONT BIGGER;
    FONT *fontScore =load_font("Fonts/showScore.pcx",NULL,NULL);

    char m,store;
    string hint;//store hint
    while(true){ //KIND OF TIRCKY IMPLEMENTATION, :O
        if(key[KEY_DOWN] || key[KEY_S]){  //MOVEMENT
            if((ix+1>=0&&ix+1<MAZE_SIZE)){
                if(maze[ix+1][iy]=='.'){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix+1][iy];
                    maze[ix+1][iy]=store;
                    ix++;
                    px+=30;
                    if(score-1<0)score=0;
                    else score--;
                    rest(90);//delay ms
                }else if(maze[ix+1][iy]=='S'){
                    win_game(score,0);
                    break;
                }
            }
        }else if(key[KEY_UP] || key[KEY_W]){
            if(ix-1>=0&&ix-1<MAZE_SIZE){
                if (maze[ix-1][iy]=='.'){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix-1][iy];
                    maze[ix-1][iy]=store;
                    ix--;
                    px-=30;
                    if(score-1<0)score=0;
                    else score--;
                    rest(90);//delay ms
                }else if(maze[ix-1][iy]=='S'){
                    win_game(score,0);
                    break;
                }
            }
        }else if(key[KEY_LEFT] || key[KEY_A]){
            if(iy-1>=0&&iy-1<MAZE_SIZE){
                if(maze[ix][iy-1]=='.'){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix][iy-1];
                    maze[ix][iy-1]=store;
                    iy--;
                    py-=30;
                    if(score-1<0)score=0;
                    else score--;
                    rest(90);//delay ms
                }else if(maze[ix][iy-1]=='S'){
                    win_game(score,0);
                    break;
                }

            }
        }else if(key[KEY_RIGHT] || key[KEY_D]){
            if(iy+1>=0&&iy+1<MAZE_SIZE){
                if(maze[ix][iy+1]=='.'){
                    store=maze[ix][iy];
                    maze[ix][iy]=maze[ix][iy+1];
                    maze[ix][iy+1]=store;
                    iy++;
                    py+=30;
                    if(score-1<0)score=0;
                    else score--;
                    rest(90);//delay ms
                }else if(maze[ix][iy+1]=='S'){
                    win_game(score,0);
                    break;
                }
            }
        }

        clear(buffer);
        //MOUSE ACTIONS
        if(mouse_x > 684 && mouse_x < 835 && mouse_y > 542 && mouse_y < 587){//MENU
            blit(fondo2, buffer, 0, 0, 0, 0, 860, 660);
            if ( mouse_b & 1 ){
                px=30,py=30;
                ix=1,iy=1;
                steps_left=0;
                wipe_maze();
                break;
            }
        }else if(mouse_x > 659 && mouse_x < 857 && mouse_y > 264 && mouse_y < 330){//HINT
            blit(fondo3, buffer, 0, 0, 0, 0, 860, 660);
            if ( mouse_b & 1 ){
                hint.clear();
                visited.assign(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));//Visited vector
                dfs_Solve(ix,iy);
                visited.clear();//Wipe visited
                hint.clear();
                hint=path[path.size()-1];//hint to show
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
        //score draw
        stringstream ss;
        ss<<score;
        string as=ss.str();
        while(as.size()<4)as='0'+as;
        textprintf_ex(buffer, fontScore, 680, 125, makecol(255, 50, 50),-1, as.c_str());//show score

        if(!hint.empty())textprintf_ex(buffer, fontScore, 745, 315, makecol(255, 50, 50),-1, hint.c_str());//show hint
        blit(buffer,screen,0,0,0,0,860,660);//screen
    }
    return;
}

void arcadeGame(){
    loadBmp();//load bitmaps;
     //FONT BIGGER;
    FONT *fontScore =load_font("Fonts/showScore.pcx",NULL,NULL);
    int level=1;
    int score=120;//here score works as a timer
    double begin_time=time(NULL);//Time start
    bool playing=true;
    while(playing){
        int ix=1,iy=1;//Begining of maze
        px=py=30;
        loadMaze(ix,iy);//createMaze
        char m,store;
        string hint;//store hint
        if(level)
        while(true){ //KIND OF TIRCKY IMPLEMENTATION, :D
            double now=time(NULL);//actual time
            if (score==0){
                playing=false;
                win_game(level,1);
                break;
            }
            if(key[KEY_DOWN] || key[KEY_S]){  //MOVEMENT
                if((ix+1>=0&&ix+1<MAZE_SIZE)){
                    if(maze[ix+1][iy]=='.'){
                        store=maze[ix][iy];
                        maze[ix][iy]=maze[ix+1][iy];
                        maze[ix+1][iy]=store;
                        ix++;
                        px+=30;
                        rest(90);//delay ms
                    }else if(maze[ix+1][iy]=='S'){
                        wipe_maze();
                        level++;
                        break;
                    }
                }
            }else if(key[KEY_UP] || key[KEY_W]){
                if(ix-1>=0&&ix-1<MAZE_SIZE){
                    if (maze[ix-1][iy]=='.'){
                        store=maze[ix][iy];
                        maze[ix][iy]=maze[ix-1][iy];
                        maze[ix-1][iy]=store;
                        ix--;
                        px-=30;
                        rest(90);//delay ms
                    }else if(maze[ix-1][iy]=='S'){
                        wipe_maze();
                        level++;
                        break;
                    }
                }
            }else if(key[KEY_LEFT] || key[KEY_A]){
                if(iy-1>=0&&iy-1<MAZE_SIZE){
                    if(maze[ix][iy-1]=='.'){
                        store=maze[ix][iy];
                        maze[ix][iy]=maze[ix][iy-1];
                        maze[ix][iy-1]=store;
                        iy--;
                        py-=30;
                        rest(90);//delay ms
                    }else if(maze[ix][iy-1]=='S'){
                        wipe_maze();
                        level++;
                        break;
                    }

                }
            }else if(key[KEY_RIGHT] || key[KEY_D]){
                if(iy+1>=0&&iy+1<MAZE_SIZE){
                    if(maze[ix][iy+1]=='.'){
                        store=maze[ix][iy];
                        maze[ix][iy]=maze[ix][iy+1];
                        maze[ix][iy+1]=store;
                        iy++;
                        py+=30;
                        rest(90);//delay ms
                    }else if(maze[ix][iy+1]=='S'){
                        wipe_maze();
                        level++;
                        break;
                    }
                }
            }

            clear(buffer);
            //MOUSE ACTIONS
            if(mouse_x > 684 && mouse_x < 835 && mouse_y > 542 && mouse_y < 587){//MENU
                blit(fondo2, buffer, 0, 0, 0, 0, 860, 660);
                if ( mouse_b & 1 ){
                    px=30,py=30;
                    ix=1,iy=1;
                    steps_left=0;
                    wipe_maze();
                    win_game(level,1);
                    return;
                }
            }else if(mouse_x > 659 && mouse_x < 857 && mouse_y > 264 && mouse_y < 330){//HINT
                blit(fondo3, buffer, 0, 0, 0, 0, 860, 660);
                if ( mouse_b & 1 ){
                    hint.clear();
                    visited.assign(MAZE_SIZE,vector<bool>(MAZE_SIZE,0));//Visited vector
                    dfs_Solve(ix,iy);
                    visited.clear();//Wipe visited
                    hint.clear();
                    hint=path[path.size()-1];//hint to show
                    path.clear();
                    score-=5;
                    if(score<0)score=0;
                    rest(90);
                }
            }else{
                blit(fondo1, buffer, 0, 0, 0, 0, 860, 660);
            }
            drw_maze(); //draw maze
            draw_sprite(buffer, player,py,px); //draw player
            //DRAW SCORE + CURRENT LEVEL
            stringstream ss,lv;
            ss<<score; lv<<level;
            string as=ss.str();string lev=lv.str();
            while(as.size()<3)as='0'+as;
            as+='-'+lev;
            textprintf_ex(buffer, fontScore, 665, 125, makecol(255, 50, 50),-1, as.c_str());//show score
            if(!hint.empty())textprintf_ex(buffer, fontScore, 745, 315, makecol(255, 50, 50),-1, hint.c_str());//show hint
            blit(buffer,screen,0,0,0,0,860,660);//screen

            //SOCRE COUNTER
            if((int)(begin_time)!=(int)(now)){//each second
                begin_time=now;
                now=time(NULL);
                score--;
            }
        }
    }
    return;
}
