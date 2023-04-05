#include <K32_presets.h>
#include <K32_mods.h>

class BankStrobe : public LBank
{
public:
    BankStrobe() : LBank(20)
    {
        //    0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19
        //   dim,stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4,FVol,Fint,FDur,

        add( 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 00 OFF

        add( 255, 255, 255, 255, 250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 01 str blanc rapide
        
        add( 255, 255, 255, 255, 250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 02 str blanc rapide fade out 5 sec
        mem->mod(new K32_mod_fadeout)->period(5000)->at(0)->mini(0)->maxi(255);

        add( 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 03 OFF

        add( 255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 04 ruby
        mem->mod(new K32_mod_sinus)->period(2000)->at(0)->phase(0)->mini(127)->maxi(255);
        
        add( 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 05 OFF
        
        add( 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 06 police + fog
        mem->mod(new K32_mod_sawtooth)->period(500)->at(2)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_isawtooth)->period(500)->at(4)->phase(0)->mini(0)->maxi(255);
        mem->mod(new K32_mod_fadeout)->period(10000)->at(17)->mini(0)->maxi(255);
        
        add( 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 07 OFF
        
        add( 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); // 08 OFF
        
    }
};

//         add( 255, 240, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); //  cho

//         add( 255, 200, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); //  froid

//         add( 255, 000, 255, 255, 250, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000 ); //  blanc