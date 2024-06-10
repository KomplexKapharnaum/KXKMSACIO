#include <K32_presets.h>

class BankArca : public LBank
{
public:
    BankArca() : LBank(7)
    {
        // {000, 001, 002, 003, 004, 005, 006} adr + -1
        // {  r,   g,   b,   w, str,macr, dim}
        add(255, 000, 000, 000, 000, 000, 255); // 00 Red
        add(000, 255, 000, 000, 000, 000, 255); // 01 Green
        add(000, 000, 255, 000, 000, 000, 255); // 02 Blue
        add(255, 255, 255, 000, 000, 000, 255); // 03 White
        add(255, 255, 255, 000, 000, 000, 255); // 04 rvb **3 4 5**
        mem->mod(new K32_mod_sinus)->at(000)->period(8500)->phase(000)->mini(000)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(90)->mini(000)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(180)->mini(000)->maxi(255);

        add(000, 000, 000, 255, 029, 000, 255); // 05 str rnd 67
        add(000, 000, 000, 255, 058, 000, 255); // 06 str all 67
        mem->mod(new K32_mod_pulse)->at(1)->at(2)->at(000)->param(1, 10)->period(70);

        add(000, 000, 000, 255, 000, 100, 255); // 07 str all 42
        add(000, 000, 000, 255, 000, 230, 255); // 08 str all lent
        add(000, 000, 000, 255, 000, 000, 255); // 09 circule w **9** 20>255
        mem->mod(new K32_mod_sinus)->at(6)->mini(100)->maxi(255)->period(2000);

        add(255, 255, 255, 255, 000, 000, 255); // 10 circus w b **7** 1>255
        mem->mod(new K32_mod_sinus)->at(1)->at(000)->at(4)->period(8500)->phase(000)->mini(000)->maxi(255);

        add(255, 255, 255, 255, 000, 000, 255); // 11 str w -> blue
        mem->mod(new K32_mod_pulse)->at(1)->at(000)->at(4)->param(1, 100)->period(7000);

        add(255, 255, 255, 000, 010, 000, 255); // 12 color form
        mem->mod(new K32_mod_sinus)->at(000)->period(8500)->phase(000)->mini(000)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(120)->mini(000)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(240)->mini(000)->maxi(255);

        add(000, 127, 255, 000, 000, 000, 255); // 13 blue parcielle
        add(000, 080, 200, 000, 000, 000, 255);  // 14 respi blue **000**38 > 217
        mem->mod(new K32_mod_sinus)->at(6)->period(8500)->mini(38)->maxi(217);

        add(000, 000, 000, 000, 000, 000, 000); // 15 BLACK stm leave lset mem

     nowifi(255, 000, 000, 000, 000, 000, 010);
    }
};
