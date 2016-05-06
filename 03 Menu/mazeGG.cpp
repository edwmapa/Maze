#include<bits/stdc++.h>
#include<allegro.h>
#include "normal.h"
using namespace std;

int main(){
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 860, 660, 0, 0);

    //bitmap menu
    BITMAP *buffer=create_bitmap(860, 660);
    BITMAP *cursor=load_bitmap("cursor.bmp",NULL);
    BITMAP *fondo=load_bitmap("Menu_1.bmp",NULL);
    BITMAP *arcade=load_bitmap("Menu_2.bmp",NULL);
    BITMAP *normal=load_bitmap("Menu_3.bmp",NULL);
    BITMAP *scoreboard=load_bitmap("Menu_4.bmp",NULL);
    BITMAP *salir=load_bitmap("Menu_5.bmp",NULL);
    //loop choose
    bool exit_Menu=false;
    while(!exit_Menu){
        if ( mouse_x > 325 && mouse_x < 588 && mouse_y > 223 && mouse_y < 293){//arcade
            blit(arcade, buffer, 0, 0, 0, 0, 860, 660);
        }else if(mouse_x > 330 && mouse_x < 595 && mouse_y > 331 && mouse_y < 395){//normal
            if ( mouse_b & 1 ){
                clear_bitmap(screen); //cls
                normalGame();
            }
            blit(normal, buffer, 0, 0, 0, 0, 860, 660);
        }else if(mouse_x > 249 && mouse_x < 606 && mouse_y > 443 && mouse_y < 497){//score
            blit(scoreboard, buffer, 0, 0, 0, 0, 860, 660);
        }else if(mouse_x > 372 && mouse_x < 541 && mouse_y > 538 && mouse_y < 603){//exit
            blit(salir, buffer, 0, 0, 0, 0, 860, 660);
            if ( mouse_b & 1 )exit_Menu = true;
        }else{
            blit(fondo, buffer, 0, 0, 0, 0, 860, 660);
        }
        //show screen
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);
        blit(buffer, screen, 0, 0, 0, 0, 860, 660);

    }

}
END_OF_MAIN();
