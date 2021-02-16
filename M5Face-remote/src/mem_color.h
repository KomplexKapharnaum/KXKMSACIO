#ifndef mem_color_h
#define mem_color_h

#ifndef number_mem
#define number_mem 10
#endif

uint8_t MEM_COLOR[number_mem][4] = {
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

String NAME_MEM_COLOR[number_mem] = {
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

#endif