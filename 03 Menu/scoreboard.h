#include<bits/stdc++.h>
#include <allegro.h>
using namespace std;

vector<string>whole_arcade(11,"");//Formated as:  score-name-date
vector<string>whole_normal(11,"");//Formated as:  score-name-date

void load_scores(string fa,string fb){
    int worthlessValue;
    string sc,name,date;
    ifstream fina(fa);
    ifstream finb(fb);
    fina>>worthlessValue;//Really, I don't care about this value
    finb>>worthlessValue;//Neither this one
    for(int i=0;i<10;i++){
        fina>>sc>>name>>date;//arcade
        whole_arcade[i]=sc+"-"+name+"-"+date;

        finb>>sc>>name>>date;//normal
        whole_normal[i]=sc+"-"+name+"-"+date;
    }
    fina.close();
    finb.close();
    return;
}

void show_scores(){
    srand(time(NULL));
    string arcade="Scores/arcade_score.sc";
    string normal="Scores/normal_score.sc";
    BITMAP *buff=background=load_bitmap("Img/Scoreboard.bmp",NULL);
    FONT *newFont = load_font("Fonts/scoreboardFonts.pcx",NULL,NULL);
    FONT *fontTitle =load_font("Fonts/showScore.pcx",NULL,NULL);
    load_scores(arcade,normal);
    while(true){//TRICKY AGAIN JEJE
        int y=280,r=0;//init position arcade and normal text
        if(key[KEY_ESC]){
            if(alert("Desea salir de los puntajes?", NULL,NULL,"&Si", "&No", 's', 'n')==1)return;
            else continue;
        }
        textprintf_ex(buff, fontTitle, 115, 180, makecol(255, 50, 50),-1, "NORMAL");//show tile normal
        textprintf_ex(buff, fontTitle, 470, 180, makecol(50, 50, 255),-1, "ARCADE");//show title arcade
        textprintf_ex(buff, newFont, 115, 250, makecol(255, 50, 50),-1, "SCORE/NAME/DATE");//show header normal
        textprintf_ex(buff, newFont, 470, 250, makecol(50, 50, 255),-1, "LEVEL/NAME/DATE");//show header arcade
        for(int i=0;i<10;i++){
            textprintf_ex(buff, newFont, 80, y, makecol(r, 255, r),-1, "%d",i);//show pos
            textprintf_ex(buff, newFont, 105, y, makecol(225,128,0),-1, whole_normal[i].c_str());//show score normal
            textprintf_ex(buff, newFont, 470, y, makecol(255,128,0),-1, whole_arcade[i].c_str());//show score arcade
            r+=25;
            y+=30;
        }
        textprintf_ex(buff, font, 67, 190, makecol(255, 255, 255),-1, "Presione [ESC] para regresar...");//print message escape
        blit(buff,screen,0,0,0,0,860,660);
    }
    return;
}
