#ifndef preset_color_str_h
#define preset_color_str_h

#ifndef number_mem
#define number_mem 10
#endif

uint8_t PRESET_COLOR_STR[number_mem][3] = {
    {000, 000, 000}, // 00 NOIR
    {255, 000, 000}, // 01 RED
    {000, 255, 000}, // 02 GREEN
    {000, 000, 255}, // 03 BLUE
    {255, 255, 161}, // 04 WHITE
    {255, 127, 000}, // 05 ORANGE
    {255, 255, 000}, // 06 YELLOW
    {000, 255, 255}, // 07 CYAN
    {255, 000, 255}, // 08 MAGENTA
    {255, 255, 255}, // 09 FULL ALL
};
//  {red,gree,blue,whit}

String NAME_PRESET_COLOR_STR[number_mem] = {
    " NOIR ",  // 0
    " RED ",      // 1
    " GREEN ",    // 2
    " BLUE ",     // 3
    " WHITE ",    // 4
    " ORANGE ",   // 5
    " YELLOW ",   // 6
    " CYAN ",     // 7
    " MAGENTA ",  // 8
    " FULL ALL ", // 9
};

uint8_t PRESET_RED[number_mem] = {
    0,      // 00 
    25,     // 01 
    50,     // 02 
    75,     // 03 
    100,    // 04 
    125,    // 05 
    150,    // 06 
    175,    // 07 
    200,    // 08 
    225,    // 09 
};

String NAME_PRESET_RED[number_mem] = {
    " 0 ",          //00
    " 25 ",         //01
    " 50 ",         //02
    " 75 ",         //03
    " 100 ",        //04
    " 125 ",        //05
    " 150 ",        //06
    " 175 ",        //07
    " 200 ",        //08
    " 225 ",        //09
};

uint8_t PRESET_GREEN[number_mem] = {
    0,      // 00 
    25,     // 01 
    50,     // 02 
    75,     // 03 
    100,    // 04 
    125,    // 05 
    150,    // 06 
    175,    // 07 
    200,    // 08 
    225,    // 09 
};

String NAME_PRESET_GREEN[number_mem] = {
    " 0 ",          //00
    " 25 ",         //01
    " 50 ",         //02
    " 75 ",         //03
    " 100 ",        //04
    " 125 ",        //05
    " 150 ",        //06
    " 175 ",        //07
    " 200 ",        //08
    " 225 ",        //09
};

uint8_t PRESET_BLUE[number_mem] = {
    0,      // 00 
    25,     // 01 
    50,     // 02 
    75,     // 03 
    100,    // 04 
    125,    // 05 
    150,    // 06 
    175,    // 07 
    200,    // 08 
    225,    // 09 
};

String NAME_PRESET_BLUR[number_mem] = {
    " 0 ",          //00
    " 25 ",         //01
    " 50 ",         //02
    " 75 ",         //03
    " 100 ",        //04
    " 125 ",        //05
    " 150 ",        //06
    " 175 ",        //07
    " 200 ",        //08
    " 225 ",        //09
};



#endif