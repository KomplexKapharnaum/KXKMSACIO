
void main_menu();
void powerOff();

#include "lulu_menu.h"
#include "audio_menu.h"
#include "monitor_menu.h"

void main_menu()
{
    ezMenu main_menu("Welcome to M5");
    main_menu.txtBig();
    main_menu.addItem("REMOTE LULU", remote_lulu);
    main_menu.addItem("REMOTE AUDIO", remote_audio);
    main_menu.addItem("MONITOR", monitor_menu);
    main_menu.addItem("SET UP", ez.settings.menu);
    main_menu.addItem("POWER OFF", powerOff);
    main_menu.upOnFirst("last|up");
    main_menu.downOnLast("first|down");
    main_menu.run();
}

void powerOff() { m5.powerOFF(); }