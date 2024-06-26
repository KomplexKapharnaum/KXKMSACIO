#include <K32_presets.h>
#include <K32_mods.h>

class BankStrobe : public LBank
{
public:
    BankStrobe() : LBank(17)
    {
        //        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
        //       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4

        add( 255, 000, 255, 112, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 00 attente lampe a sel
        mem->mod(new K32_mod_fadein)->period(3000)->at(0)->mini(0)->maxi(255);

        add( 255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 01 Marin
        mem->mod(new K32_mod_sinus)->period(2000)->at(3)->phase(0)->mini(0)->maxi(88);

        add( 255, 000, 000, 120,  18, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 02 foret
        mem->mod(new K32_mod_sinus)->period(3000)->at(3)->phase(0)->mini(110)->maxi(120);
        mem->mod(new K32_mod_sinus)->period(3000)->at(4)->phase(90)->mini(0)->maxi(18);

        add( 255, 210, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 03 Marin qui deraille
        mem->mod(new K32_mod_sinus)->period(2000)->at(3)->phase(0)->mini(0)->maxi(88);
        mem->mod(new K32_mod_fadein)->period(45000)->at(1)->mini(0)->maxi(210);
        mem->mod(new K32_mod_random)->additive()->period(1500)->at(1)->mini(-200)->maxi(-100);

        add( 255, 210, 000, 120,  18, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 04 foret qui deraille
        mem->mod(new K32_mod_sinus)->period(3000)->at(3)->phase(0)->mini(110)->maxi(120);
        mem->mod(new K32_mod_sinus)->period(3000)->at(4)->phase(90)->mini(0)->maxi(18);
        mem->mod(new K32_mod_fadein)->period(45000)->at(1)->mini(0)->maxi(210);
        mem->mod(new K32_mod_random)->additive()->period(1000)->at(1)->mini(-200)->maxi(-50);

        add( 255, 000, 255, 255, 250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 05 blanc str
        mem->mod(new K32_mod_sinus)->period(1000)->at(1)->phase(0)->mini(0)->maxi(255);

        add( 255, 255, 255, 255, 250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 06 str blanc rapide 
        
        add( 255, 000, 255,  255,  250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 07 W fade in
        mem->mod(new K32_mod_fadein)->period(5000)->at(0)->mini(0)->maxi(255);

        add( 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 08 noir
    }
};

//         add( 255, 240, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); //  cho

//         add( 255, 200, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); //  froid

//         add( 255, 000, 255, 255, 250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); //  blanc
