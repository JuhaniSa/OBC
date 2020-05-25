#include <Arduino.h>
#include "menu.h"


Menu::menu

void Menu::menu_up(){
    if (current_pos < sizeof(menu_pages))
    current_pos = current_pos + 1;
    else{
        current_pos = 0;
    }
}

void Menu::menu_down(){
    if (current_pos > 0){
    current_pos = current_pos - 1;
    }
    else current_pos = sizeof(menu_pages);
    

};
