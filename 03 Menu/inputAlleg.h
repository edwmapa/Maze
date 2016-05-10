#include <allegro.h>
#include<bits/stdc++.h>
using namespace std;

//CODE MODIFIED FROM https://jadendreamer.wordpress.com/2007/11/14/alternative-text-input-not-using-allegro-gui/
string input_form(){
    BITMAP* container=load_bitmap("Img/Input_form.bmp",NULL);
    BITMAP* buff=create_bitmap(860,660);
    string  edittext;                         // an empty string for editting
    string::iterator iter = edittext.begin(); // string iterator
    int caret  = 0;                       // tracks the text caret
    bool insert = true;
    while(edittext.size()<3){
        while(keypressed()){
            int  newkey = readkey();
            char ASCII = newkey & 0xff;
            char scancode = newkey >> 8;
            if((ASCII >='A' && ASCII <='Z') || (ASCII >='a' && ASCII <='z')){// 65=A, 90=Z, 97=a, 122=z
                if(ASCII >='a' && ASCII <='z')ASCII-=32;
            // add the new char, inserting or replacing as need be
                if(insert || iter == edittext.end())iter = edittext.insert(iter, ASCII);
                else edittext.replace(caret, 1, 1, ASCII);
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
                    case KEY_ESC:
                        break;
                    default:
                        break;
                }
            }
        }
        //output in container
        clear(buff);
        draw_sprite(buff,container,0,0);
        textprintf_ex(buff, font, 345, 305, makecol(0, 0, 0),-1, "Ingrese sus iniciales");
        textprintf_ex(buff, font, 380, 320, makecol(0, 0, 0),-1, "(3 caracteres)");
        textprintf_ex(buff, font, 415, 345, makecol(255, 0, 0),-1, edittext.c_str());
        blit(buff,screen,0, 0, 0, 0, 860, 660);
    }
    rest(500);
    destroy_bitmap(container);
    //set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    return edittext;
}
