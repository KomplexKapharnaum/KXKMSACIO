#include <K32_presets.h>

class BankP5 : public LBank
{
public:
    BankP5() : LBank(6)
    {
        //     {0      , 1  , 2  , 3  , 4  , 5 } adr + -1
        //     {   str , dim, r  , g  , b  , w }
        //     {master , r  , g  , b  , str }
        add(    0, 255, 255,   0,   0,   0); // 00 Red
        add(    0, 255,   0, 255,   0,   0); // 01 Green
        add(    0, 255,   0,   0, 255,   0); // 02 Blue
        add(    0, 255,   0,   0,   0, 255); // 03 White
        add(    0, 255, 255, 255, 255,   0); // 04 rvb **3 4 5**
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(4)->period(8500)->phase(180)->mini(0)->maxi(255);

        add(   29, 255,   0,   0,   0, 255); // 05 str rnd 67
        add(   58, 255,   0,   0,   0, 255); // 06 str all 67
        mem->mod(new K32_mod_pulse)->at(2)->at(3)->at(4)->param(1, 10)->period(70);
    
        add(  100, 255,   0,   0,   0, 255); // 07 str all 42
        add(  230, 255,   0,   0,   0, 255); // 08 str all lent
        add(   0, 255, 255, 255, 255, 255); // 09 circule w **9** 20>255
        mem->mod(new K32_mod_sinus)->at(1)->mini(100)->maxi(255)->period(2000);

        add(    0, 255, 255, 255, 255, 255); // 10 circus w b **7** 1>255
        mem->mod(new K32_mod_sinus)->at(2)->at(3)->at(4)->at(5)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(   89, 255, 255, 255, 255, 255); // 11 str w -> blue
        mem->mod(new K32_mod_pulse)->at(2)->at(3)->at(5)->param(1, 100)->period(7000);

        add(   10, 255, 255, 255, 255,   0); // 12 color form
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(120)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(4)->period(8500)->phase(240)->mini(0)->maxi(255);

        add(    0, 255,   0, 127, 255,   0); // 13 blue parcielle
        add(    0, 255,   0,  80, 200,   0); // 14 respi blue **0**38 > 217 
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->mini(38)->maxi(217);

        add(    0,   0,   0,   0,   0,   0); // 15 BLACK stm leave lset mem
    
     nowifi(    0, 255,  127,  12,  92,  0);
    }
};
