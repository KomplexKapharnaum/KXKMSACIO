#include <K32_presets.h>

class BankP5 : public LBank
{
public:
    BankP5() : LBank(6)
    {
        // {000, 001, 002, 003, 004, 005}
        // {Str, Dim,   r,   g,   b,   w}
        add(255, 255, 000, 000, 000, 000); // 00 Noir
        add(255, 255, 000, 000, 000, 127); // 01 Blanc Faible
        add(255, 255, 135, 117,  58, 000); // 02 sepia Faible
        add(117, 255, 000, 000, 000, 255); // 03 White Strobe
        add(255, 255, 135, 117,  58, 000); // 04 sepia faible Pti Modulo
        mem->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(180)->maxi(255);
        add(127, 255, 255, 255, 255, 255); // 05 Super8
        mem->mod(new K32_mod_pulse)->at(0)->period(4000)->phase(0)->mini(127)->maxi(238);
        add(255, 255, 000, 255, 000, 000); // 06 Vert Full
        add(255, 255, 255, 255, 000, 000); // 07 Jaune
        add(255, 255, 255, 127, 000, 000); // 08 Orange
        add(255, 255, 255, 000, 000, 000); // 09 Rouge
        add(255, 255, 000, 255, 000, 000); // 10 Vert in
        mem->mod(new K32_mod_fadein)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        add(255, 255, 000, 255, 000, 000); // 11 Vert out
        mem->mod(new K32_mod_fadeout)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        add(255, 255, 255, 255, 000, 000); // 12 Jaune in
        mem->mod(new K32_mod_fadein)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        add(255, 255, 255, 255, 000, 000); // 13 Jaune out
        mem->mod(new K32_mod_fadeout)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
        add(255, 255, 255, 000, 000, 000); // 14 V->R->J
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(180)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 255, 000, 000); // 15 J->V->R
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(180)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(240)->mini(0)->maxi(255);

        add(255, 255, 000, 255, 000, 000); // 16 R->J->V
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(240)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(90)->mini(0)->maxi(255);

        add(255, 255, 000, 000, 255, 000); // 17 B->V respi
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(4)->period(10000)->phase(0)->mini(255)->maxi(0);
        mem->mod(new K32_mod_sinus)->at(1)->period(5000)->phase(180)->mini(120)->maxi(255);

        add(255, 255, 000, 255, 000, 000); // 18 V->B respi
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(255)->maxi(0);
        mem->mod(new K32_mod_sinus)->at(4)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(5000)->phase(180)->mini(120)->maxi(255);

        add(255, 255, 000, 000, 255, 000); // 19 Bleu
        add(255, 255, 000, 000, 000, 000); // 20 BLACK stm leave lset mem

     nowifi(000, 010, 255, 000, 000, 000);
    }
};
