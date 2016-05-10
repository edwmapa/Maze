#include<bits/stdc++.h>
#include "games.h"
using namespace std;

int main(){
    allegro_init();
    install_keyboard();
    install_mouse();
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 860, 660, 0, 0);

    //bitmap menu
    BITMAP *buffer=create_bitmap(860, 660);
    BITMAP *fondo=load_bitmap("Img/Menu_1.bmp",NULL);
    BITMAP *arcade=load_bitmap("Img/Menu_2.bmp",NULL);
    BITMAP *normal=load_bitmap("Img/Menu_3.bmp",NULL);
    BITMAP *scoreboard=load_bitmap("Img/Menu_4.bmp",NULL);
    BITMAP *salir=load_bitmap("Img/Menu_5.bmp",NULL);
    //loop choose
    show_mouse(screen);
    blit(buffer, screen, 0, 0, 0, 0, 860, 660);
    bool exit_Menu=false;
    while(!exit_Menu){
        if ( mouse_x > 325 && mouse_x < 588 && mouse_y > 223 && mouse_y < 293){//arcade
            if ( mouse_b & 1 )arcadeGame();
            blit(arcade, buffer, 0, 0, 0, 0, 860, 660);
        }else if(mouse_x > 330 && mouse_x < 595 && mouse_y > 331 && mouse_y < 395){//normal
            if ( mouse_b & 1 )normalGame();
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
        show_mouse(screen);
        blit(buffer, screen, 0, 0, 0, 0, 860, 660);
    }

}
END_OF_MAIN();
