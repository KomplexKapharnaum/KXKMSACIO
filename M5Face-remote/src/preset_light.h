#ifndef preset_light_h
#define preset_light_h

#ifndef number_mem
#define number_mem 10
#endif

uint8_t PRESET_COLOR[number_mem][4] = {
    {023, 023, 023, 023}, // 00 DIAL ALL
    {255, 000, 000, 000}, // 01 RED
    {000, 255, 000, 000}, // 02 GREEN
    {000, 000, 255, 000}, // 03 BLUE
    {000, 000, 000, 255}, // 04 WHITE
    {255, 127, 000, 000}, // 05 ORANGE
    {255, 255, 000, 000}, // 06 YELLOW
    {000, 255, 255, 000}, // 07 CYAN
    {255, 000, 255, 000}, // 08 MAGENTA
    {255, 255, 255, 255}, // 09 FULL ALL
};
//  {red,gree,blue,whit}

String NAME_PRESET_COLOR[number_mem] = {
    " DIA ALL ",  // 0
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

uint8_t PRESET_STR[number_mem] = {
    5,   // 00 OPEN
    15,  // 01 STR
    25,  // 02 SMOOTH
    35,  // 03 RND 1
    71,  // 04 RND 32
    90,  // 05 RND 64
    115, // 06 *BLINK
    205, // 07 0 RND 1
    228, // 08 0 RND 32
    250, // 09 O RND 64
};

String NAME_PRESET_STR[number_mem] = {
    " OPEN ",     //00
    " STR ",      //01
    " SMOOTH ",   //02
    " RND 1 ",    //03
    " RND 32 ",   //04
    " RND 64 ",   //05
    " *BLINK* ",  //06
    " O RND 1 ",   //07
    " O RND 32 ", //08
    " O RND 64 ", //09
};

uint8_t PRESET_MOD[number_mem] = {
    15, // 00 2 Colors
    25, // 01 01:02
    35, // 02 >
    45, // 03 <
    55, // 04 <>
    95, // 05 P>
    105, // 06 P<
    115, // 07 P<>
    235, // 08 TRI
    245, // 09 QUADRI
};

String NAME_PRESET_MOD[number_mem] = {
    " 2 Colors ", //00
    " 01:02 ",    //01
    " > ",        //02
    " < ",        //03
    " <> ",       //04
    " P< ",       //05
    " P> ",       //06
    " P<> ",      //07
    " TRI ",      //08
    " QUADRI ",   //09 
};

uint8_t PRESET_MIRROR[number_mem] = {
    00,  // 00 No Mirr
    15,  // 01 *2 <>
    25,  // 02 *3 <><
    35,  // 03 *4 <><>
    45,  // 04 *2 <<
    55,  // 05 *3 <<<
    65,  // 06 *4 <<<<
    00,  // 07 
    00,  // 08 
    255, // 09 Force Artnet
};

String NAME_PRESET_MIRROR[number_mem] = {
    " No Mirr ",        //00
    " *2 <> ",          //01
    " *3 <>< ",         //02
    " *4 <><> ",        //03
    " *2 << ",          //04
    " *3 <<< ",         //05
    " *4 <<<< ",        //06
    " No Mirr ",        //07
    " No Mirr ",        //08
    " Force Artnet ",   //09 
};

#endif