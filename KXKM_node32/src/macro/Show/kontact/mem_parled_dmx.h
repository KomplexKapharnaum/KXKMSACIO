#include <K32_presets.h>

class BankPar : public LBank
{
public:
    BankPar() : LBank(5)
    {
        // {000, 001, 002, 003, 004} adr + -1
        // {mas, r  , g  , b  , str }
        add(255, 000, 000, 000, 000); // 00 Noir
        add(255, 108, 127, 102, 000); // 01 Blanc Faible
        mem->mod(new K32_mod_fadein)->at(0)->period(50000)->phase(0)->mini(0)->maxi(100);
        add(255, 122, 127,  47, 000); // 02 sepia Faible
        add(255, 255, 255, 255,  76); // 03 White Strobe
        add(255, 122, 127,  47, 000); // 04 sepia faible Pti Modulo
        mem->mod(new K32_mod_sinus)->at(0)->period(8500)->phase(0)->mini(100)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(5000)->phase(35)->mini(100)->maxi(150); //modulo sur le vert
        mem->mod(new K32_mod_sinus)->at(1)->period(5000)->phase(35)->mini(200)->maxi(100); //modulo sur le rouge
        add(255, 255, 255, 255,  28); // 05 Super8
        mem->mod(new K32_mod_pulse)->at(4)->period(4000)->phase(0)->mini(28)->maxi(13);
        add(255, 000, 255, 000, 000); // 06 Disco color
        mem->mod(new K32_mod_random)->at(1)->period(500)->phase(0)->mini(0)->maxi(255); // modulo r
        mem->mod(new K32_mod_random)->at(2)->period(500)->phase(60)->mini(0)->maxi(255); // modulo g
        mem->mod(new K32_mod_random)->at(3)->period(500)->phase(180)->mini(0)->maxi(255); // modulo b
        add(255, 255, 255, 000, 000); // 07 Jaune
        add(255, 255, 127, 000, 000); // 08 Orange
        add(255, 255, 000, 000, 76); // 09 Rouge
        add(255, 000, 255, 000, 000); // 10 Vert in
        mem->mod(new K32_mod_fadein)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 000, 255, 000, 000); // 11 Vert out
        mem->mod(new K32_mod_fadeout)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 000, 000); // 12 Jaune in
        mem->mod(new K32_mod_fadein)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 000, 000); // 13 Jaune out
        mem->mod(new K32_mod_fadeout)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 000, 000, 000); // 14 V->R->J
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(180)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 255, 000, 000); // 15 J->V->R
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(180)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(240)->mini(0)->maxi(255);

        add(255, 000, 255, 000, 000); // 16 R->J->V
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(240)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(90)->mini(0)->maxi(255);

        add(255, 000, 000, 255, 000); // 17 B->V respi
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(255)->maxi(0);
        mem->mod(new K32_mod_sinus)->at(0)->period(5000)->phase(180)->mini(120)->maxi(255);

        add(255, 000, 255, 000, 000); // 18 V->B respi
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(255)->maxi(0);
        mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(0)->period(5000)->phase(180)->mini(120)->maxi(255);

        add(255, 000, 000, 255, 000); // 19 Bleu
        add(255, 000, 000, 000, 000); // 20 BLACK stm leave lset mem
     nowifi(255, 000, 000, 000, 000);
    }
};
