#ifndef Menu_h
#define Menu_h
#include <Arduino.h>

class Menu
{
    public:
    
    void menu_up();
    void  menu_down();
    String menu_pages[] = {};
    unsigned int current_pos;

  
};


#endif