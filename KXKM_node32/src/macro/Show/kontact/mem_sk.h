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
                add(255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 00 Blanc
                mem->mod(new K32_mod_sinus)->at(0)->period(5000)->phase(0)->mini(50)->maxi(255); // modulo sur master

                add(255, 255, 000, 000, 000, 000, 000, 000,  000, 000, 000, 000, 000, 000, 000, 255);  // 01 Rouge 
                // add(255, 255, 255, 000, 000, 000, 000, 000,  000, 000, 000, 000, 000, 000, 000, 255);  // 01 jaune  
                // add(255, 000, 255, 000, 000, 000, 000, 000,  000, 000, 000, 000, 000, 000, 000, 255);  // 01 vert 
                mem->mod(new K32_mod_random)->at(0)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI


                add(255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 02 sepia faible Pti Modulo entre vert et sépia.
                mem->mod(new K32_mod_pulse)->at(1)->param(0, 400)->period(600); //modulo sur le rouge
                mem->mod(new K32_mod_pulse)->at(2)->phase(120)->param(0, 400)->period(600); //modulo sur le vert

                add(255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 255); // 03 Blanc

                add(255, 000, 000, 000, 255, 000, 000, 000, 15, 180, 000, 000, 000, 000, 000, 255); // 04 Blanc Strobe
                mem->mod(new K32_mod_random)->at(0)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI


                add(255, 000, 000, 000, 255, 000, 000, 000, 80, 180, 000, 000, 000, 000, 000, 255);  // 05 White Strobe
                mem->mod(new K32_mod_random)->at(0)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI

                add(255, 000, 000, 000, 255, 000, 000, 000, 80, 180, 000, 000, 000, 000, 000, 255);  // 05 White Strobe
                mem->mod(new K32_mod_random)->at(0)->period(8500)->phase(0)->mini(255)->maxi(255); // modulo pour rémission SPI

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
                add(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0); // 05 Super8
               
        }
};