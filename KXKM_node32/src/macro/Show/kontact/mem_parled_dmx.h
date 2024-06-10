#include <K32_presets.h>

class BankPar : public LBank
{
public:
    BankPar() : LBank(5)
    {
        // {000, 001, 002, 003, 004} adr + -1
        // {mas, r  , g  , b  , str }
        add(255, 255, 000, 000, 000); // 00 Red
        add(255, 000, 255, 000, 000); // 01 Green
        add(255, 000, 000, 255, 000); // 02 Blue
        add(255, 255, 255, 255, 000); // 03 White
        add(255, 255, 255, 255, 000); // 04 rvb **3 4 5**
        mem->mod(new K32_mod_sinus)->at(1)->at(5)->at(6)->at(7)->at(8)->period(8500)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(180)->mini(0)->maxi(255);

        add(255, 255, 255, 255, 209); // 05 str rnd 67
        add(255, 255, 255, 255,  58); // 06 str all 67
        mem->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->at(7)->at(8)->at(6)->at(5)->param(1, 10)->period(70);

        add(255, 255, 255, 255, 100); // 07 str all 42
        add(255, 255, 255, 255, 230); // 08 str all lent
        add(255, 255, 255, 255, 000); // 09 circule w **9** 20>255
        mem->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);

        add(255, 255, 255, 255, 000); // 10 circus w b **7** 1>255
        mem->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 255,  89); // 11 str w -> blue
        mem->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);

        add(255, 255, 255, 255, 010); // 12 color form
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);

        add(255, 000, 127, 255, 000); // 13 blue parcielle
        add(255, 000,  80, 200, 000); // 14 respi blue **000**38 > 217
        mem->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);

        add(255, 000, 000, 000, 000); // 15 BLACK stm leave lset mem
     nowifi(255, 000, 000, 000, 000);
    }
};
