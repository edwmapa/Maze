#include <allegro.h>
#include<bits/stdc++.h>
using namespace std;
//CODE MODIFIED FROM https://jadendreamer.wordpress.com/2007/11/14/alternative-text-input-not-using-allegro-gui/

string input_form(){
    BITMAP* container=create_bitmap(860,660);
    string  edittext;                         // an empty string for editting
    string::iterator iter = edittext.begin(); // string iterator
    int caret  = 0;                       // tracks the text caret
    bool insert = true;
    textprintf(container, font,  260, 300, makecol(255,255,255), "Ingrese sus Iniciales (3 caracteres): ");
    blit(container,screen,0, 0, 0, 0, 860, 660);
    while(edittext.size()<3){
        while(keypressed()){
            int  newkey = readkey();
            char ASCII = newkey & 0xff;
            char scancode = newkey >> 8;
            if(ASCII >= 32 && ASCII <= 126){
            // add the new char, inserting or replacing as need be
                if(insert || iter == edittext.end())
                   iter = edittext.insert(iter, ASCII);
                else
                   edittext.replace(caret, 1, 1, ASCII);

                // increment both the caret and the iterator
                caret++;
                iter++;
            }else{
                switch(scancode){
                    case KEY_DEL:
                        if(iter != edittext.end()) iter = edittext.erase(iter);
                        break;
                    case KEY_BACKSPACE:
                        if(iter != edittext.begin()){
                            caret--;
                            iter--;
                            iter = edittext.erase(iter);
                        }
                        break;
                    default:
                        break;
                }
            }
            // clear screen
            clear(container);
            //output in container

            textprintf(container, font,  260, 300, makecol(255,255,255), "Ingrese sus Iniciales (3 caracteres): ");
            textout(container, font, edittext.c_str(), 300, 340, makecol(255,255,255));
            vline(container,caret * 8, 8, 18, makecol(0,0,0));
            blit(container,screen,0, 0, 0, 0, 860, 660);
        }
    }
    rest(500);
    destroy_bitmap(container);
    //set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    return edittext;
}
