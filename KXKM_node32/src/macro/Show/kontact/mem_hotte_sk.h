#include <K32_presets.h>

#define STRIP_PATCHSIZE 16

//
// MEM ANIMATOR DATA
//

class BankSK : public LBank
{
public:
        BankSK() : LBank(STRIP_PATCHSIZE)
        {
                // {                                                   r_,  g_,  b_,  w_, mir,      }
                // {                         pix, pix, pix, str, spe, fon, fon, fon, fon, ror,      }
                // {mas,   r,   g,   b,   w, mod,long, pos, mod,  ed,   d,   d,   d,   d, mod, zoom }
                // {000, 001, 002, 003, 004, 005, 006, 007, 008, 009, 010, 011, 012, 013, 014, 015} adr + -1
                add(255, 000, 000, 000, 255, 015, 075, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 00 Blanc 
                mem->mod(new K32_mod_sinus)->at(7)->period(2000)->phase(0)->mini(50)->maxi(230); // modulo sur position

                add(255, 000, 000, 000, 255, 015, 075, 000, 000, 000, 000, 000, 255, 000, 000, 255); // 01 Blanc bleu
                mem->mod(new K32_mod_sinus)->at(7)->period(2000)->phase(0)->mini(50)->maxi(230); // modulo sur position

                add(255, 200, 137, 60, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 02 sepia Faible
                mem->mod(new K32_mod_random)->at(1)->period(8500)->phase(0)->mini(200)->maxi(200); // modulo pour rémission SPI
                //        add(255, 122, 127,  47, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 02 sepia Faible

                add(255, 000, 000, 000, 255, 000, 000, 000, 80, 180, 000, 000, 000, 000, 000, 255);  // 03 White Strobe
                add(255, 200, 137, 60, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 04 sepia faible Pti Modulo
                mem->mod(new K32_mod_sinus)->at(0)->period(8500)->phase(0)->mini(180)->maxi(255);

                add(255, 000, 0, 0, 255, 000, 000, 000,  15, 200, 000, 000, 000, 000, 000, 255); // 05 Super8
                mem->mod(new K32_mod_pulse)->at(9)->period(4000)->phase(0)->mini(200)->maxi(17);
                //        mem->mod(new K32_mod_pulse)->at(9)->period(4000)->phase(0)->mini(200)->maxi(255);

                add(255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 06 Vert Full
                mem->mod(new K32_mod_random)->at(2)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI
                add(255, 255, 200, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 07 Jaune
                mem->mod(new K32_mod_random)->at(1)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI
                add(255, 255, 127, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 08 Orange
                mem->mod(new K32_mod_random)->at(2)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI
                add(255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 09 Rouge
                mem->mod(new K32_mod_random)->at(1)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI
                add(255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 10 Vert in
                mem->mod(new K32_mod_fadein)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

                add(255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 11 Vert out
                mem->mod(new K32_mod_fadeout)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

                add(255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 12 Jaune in
                mem->mod(new K32_mod_fadein)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

                add(255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 035, 255); // 13 Jaune out
                mem->mod(new K32_mod_fadeout)->at(0)->period(8500)->phase(0)->mini(0)->maxi(255);

                add(255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 14 V->R->J
                mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(180)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(90)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(0)->maxi(255);

                add(255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 15 J->V->R
                mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(90)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(180)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(240)->mini(0)->maxi(255);

                add(255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 16 R->J->V
                mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(240)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(1)->period(10000)->phase(0)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(90)->mini(0)->maxi(255);

                add(255, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 17 B->V respi
                mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(255)->maxi(0);
                mem->mod(new K32_mod_sinus)->at(0)->period(5000)->phase(180)->mini(120)->maxi(255);

                add(255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 18 V->B respi
                mem->mod(new K32_mod_sinus)->at(2)->period(10000)->phase(0)->mini(255)->maxi(0);
                mem->mod(new K32_mod_sinus)->at(3)->period(10000)->phase(0)->mini(0)->maxi(255);
                mem->mod(new K32_mod_sinus)->at(0)->period(5000)->phase(180)->mini(120)->maxi(255);

                add(255, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 19 Bleu
                mem->mod(new K32_mod_random)->at(3)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI
                add(255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 20 BLACK stm leave lset mem
                nowifi(10, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255);
        }
};

//
// PREVIEW PIXEL MAP
//

class BankSK_PREV : public LBank
{
public:
        BankSK_PREV() : LBank(6 * 4)
        {

                //  {r1,g1,b1,w1, r2,g2,b2,w2, r3,g3,b3,w3, r4,g4,b4,w4, r5,g5,b5,w5, r6,g6,b6,w6},
                add(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 00 Noir
                add(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 01 Blanc Faible
                add(1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 02 sepia Faible
                add(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); // 03 White Strobe
                add(1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); // 04 sepia faible Pti Modulo
                add(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0); // 05 Super8
                add(0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 06 Vert Full
                add(1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 07 Jaune
                add(1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 08 Orange
                add(1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 09 Rouge
                add(0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 10 Vert in
                add(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 11 Vert out
                add(0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 12 Jaune in
                add(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 13 Jaune out
                add(0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 14 V->R->J
                add(1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 15 J->V->R
                add(1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 16 R->J->V
                add(0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 17 B->V respi
                add(0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 18 V->B respi
                add(0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 19 Bleu
                add(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // 20 BLACK stm leave last mem
        }
};