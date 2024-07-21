#include <K32_presets.h>

class BankArca : public LBank
{
public:
    BankArca() : LBank(7)
    {
        // {000, 001, 002, 003, 004, 005, 006} adr + -1
        // {  r,   g,   b,   w, str,macr, dim}
        add(000, 000, 000, 000, 000, 000, 255); // 00 Noir
        add(000, 000, 000, 127, 000, 000, 255); // 01 Blanc faible
        mem->mod(new K32_mod_fadein)->at(6)->period(50000)->phase(0)->mini(0)->maxi(100);
        add(122, 127,  47, 000, 000, 000, 255); // 02 Sepia faible
        add(000, 000, 000, 255,  87, 000, 255); // 03 White Strobe
        add(122, 127,  47, 000, 000, 000, 255); // 04 sepia faible Pti Modulo
        mem->mod(new K32_mod_sinus)->at(6)->period(8500)->phase(0)->mini(100)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(5000)->phase(35)->mini(100)->maxi(150); //modulo sur le vert
        mem->mod(new K32_mod_sinus)->at(0)->period(5000)->phase(35)->mini(200)->maxi(100); //modulo sur le rouge
        add(255, 255, 255, 255,  35, 000, 255); // 05 Super8
        mem->mod(new K32_mod_pulse)->at(4)->period(4000)->phase(0)->mini(35)->maxi(17);
        add(000, 255, 000, 000, 000, 000, 255); // 06 Disco color
        mem->mod(new K32_mod_random)->at(0)->period(500)->phase(0)->mini(0)->maxi(255); // modulo r
        mem->mod(new K32_mod_random)->at(1)->period(500)->phase(60)->mini(0)->maxi(255); // modulo g
        mem->mod(new K32_mod_random)->at(2)->period(500)->phase(180)->mini(0)->maxi(255); // modulo b
        add(255, 255, 000, 000, 000, 000, 255); // 07 Jaune
        add(255, 127, 000, 000, 000, 000, 255); // 08 Orange
        add(255, 000, 000, 000, 87, 000, 255); // 09 Rouge strobe
        add(000, 255, 000, 000, 000, 000, 255); // 10 Vert in
        mem->mod(new K32_mod_fadein)->at(6)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(000, 255, 000, 000, 000, 000, 255); // 11 Vert out
        mem->mod(new K32_mod_fadeout)->at(6)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 000, 000, 000, 000, 255); // 12 Jaune in
        mem->mod(new K32_mod_fadein)->at(6)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 255, 000, 000, 000, 000, 255); // 13 Jaune out
        mem->mod(new K32_mod_fadeout)->at(6)->period(8500)->phase(0)->mini(0)->maxi(255);

        add(255, 000, 000, 000, 000, 000, 255); // // 14 V->R->J
        mem->mod(new K32_mod_sinus)->at(0)->period(10000)->phase(180)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(0)->period(10000)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(0)->mini(0)->maxi(255);


        add(255, 255, 000, 000, 000, 000, 255); // 15 J->V->R
        mem->mod(new K32_mod_sinus)->at(0)->period(10000)->phase(90)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(0)->period(10000)->phase(180)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(240)->mini(0)->maxi(255);

        add(000, 255, 000, 000, 000, 000, 255); // 16 R->J->V
        mem->mod(new K32_mod_sinus)->at(0)->period(10000)->phase(240)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(0)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(90)->mini(0)->maxi(255);

        add(000, 000, 255, 000, 000, 000, 255); // 17 B->V respi
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(255)->maxi(0);
        mem->mod(new K32_mod_sinus)->at(6)->period(5000)->phase(180)->mini(120)->maxi(255);

        add(000, 255, 000, 000, 000, 000, 255); // 18 V->B respi
        mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(0)->mini(255)->maxi(0);
        mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_sinus)->at(6)->period(5000)->phase(180)->mini(120)->maxi(255);

        add(000, 000, 255, 000, 000, 000, 255); // 19 Bleu
        add(000, 000, 000, 000, 000, 000, 000); // 20 BLACK stm leave lset mem

     nowifi(255, 000, 000, 000, 000, 000, 010);
    }
};
