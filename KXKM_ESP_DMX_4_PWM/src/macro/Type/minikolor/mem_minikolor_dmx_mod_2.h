#include <K32_presets.h>

class BankPars : public LBank
{
public:
    BankPars() : LBank(9)
    {

    //         {     0 , 1  , 2  , 3  ,  4  ,  5  ,   6 ,  7  , 8   }
    //         {master , r  , g  , b  ,macro, str , auto,speed, id  }
        add(mem_t{  255, 255,   0,   0,    0,    0,    0,    0,    0}); // 00 Red
        add(mem_t{  255,   0, 255,   0,    0,    0,    0,    0,    0}); // 01 Green
        add(mem_t{  255,   0,   0, 255,    0,    0,    0,    0,    0}); // 02 Blue
        add(mem_t{  255, 255, 255, 255,    0,    0,    0,    0,    0}); // 03 White
        add(mem_t{  255, 255, 255, 255,    0,    0,    0,    0,    0}); // 04 rvb **3 4 5**
        mem->mod(new K32_mod_sinus)->at(1)->at(5)->at(6)->at(7)->at(8)->period(8500)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(180)->mini(0)->maxi(255);

        add(mem_t{  255, 255, 255, 255,    0,   29,    0,    0,    0}); // 05 str rnd 67
        add(mem_t{  255, 255, 255, 255,    0,   58,    0,    0,    0}); // 06 str all 67
        mem->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->param(1, 10)->period(70);

        add(mem_t{  255, 255, 255, 255,    0,  100,    0,    0,    0}); // 07 str all 42
        add(mem_t{  255, 255, 255, 255,    0,  230,    0,    0,    0}); // 08 str all lent
        add(mem_t{  255, 255, 255, 255,    0,    0,    0,    0,    0}); // 09 circule w **9** 20>255
        mem->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);

        add(mem_t{  255, 255, 255, 255,    0,    0,    0,    0,    0}); // 10 circus w b **7** 1>255
        mem->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(mem_t{  255, 255, 255, 255,    0,   89,    0,    0,    0}); // 11 str w -> blue 
        mem->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);

        add(mem_t{  255, 255, 255, 255,    0,   10,    0,    0,    0}); // 12 color form
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);

        add(mem_t{  255,   0, 127, 255,    0,    0,    0,    0,    0}); // 13 blue parcielle
        add(mem_t{  255,   0,  80, 200,    0,    0,    0,    0,    0}); // 14 respi blue **0**38 > 217
        mem->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
         
        add(mem_t{    0,   0,   0,   0,    0,    0,    0,    0,    0}); // 15 BLACK stm leave lset mem

      nowifi(mem_t{ 255,  127,  12,  92,   0,    0,    0,    0,    0});
    }
};