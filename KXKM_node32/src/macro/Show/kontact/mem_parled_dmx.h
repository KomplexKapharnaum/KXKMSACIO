#include <K32_presets.h>

class BankPar : public LBank
{
public:
    BankPar() : LBank(5)
    {
        // {000, 001, 002, 003, 004} adr + -1
        // {mas, r  , g  , b  , str }
        add(255, 000, 000, 000, 000); // 00 Noir
        add(127, 216, 255, 204, 000); // 01 Blanc Faible
        add(127, 244, 255,  94, 000); // 02 sepia Faible
        add(255, 255, 255, 255,  76); // 03 White Strobe
        add(127, 244, 255,  94, 000); // 04 sepia faible Pti Modulo
        mem->mod(new K32_mod_sinus)->at(0)->period(8500)->phase(0)->mini(76)->maxi(178);

        add(255, 255, 255, 255,  35); // 05 Super8
        mem->mod(new K32_mod_pulse)->at(4)->period(4000)->phase(0)->mini(35)->maxi(71);

        add(255, 000, 255, 000, 000); // 06 Vert Full
        add(255, 255, 255, 000, 000); // 07 Jaune
        add(255, 255, 127, 000, 000); // 08 Orange
        add(255, 255, 000, 000, 000); // 09 Rouge
        add(255, 000, 255, 000, 000); // 10 Vert in
        mem->mod(new K32_mod_fadein)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 000, 255, 000, 000); // 11 Vert out
        mem->mod(new K32_mod_fadeout)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 000, 000); // 12 Jaune in
        mem->mod(new K32_mod_fadein)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 000, 000); // 13 Jaune out
        mem->mod(new K32_mod_fadeout)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 000, 000, 000, 000); // 14 R->J->V
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(38)->maxi(217);

        add(255, 000, 000, 000, 000); // 15 BLACK stm leave lset mem
     nowifi(255, 000, 000, 000, 000);
    }
};
