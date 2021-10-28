#include <K32_presets.h>

class BankStrobe : public LBank
{
public:
    BankStrobe() : LBank(17)
    {
        //        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
        //       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4

        add(mem_t{255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 00 Blue
            mem->route(0);

        add(mem_t{255, 000, 000, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 01 Blue cyan mod
            mem->mod(new K32_mod_sinus)->period(8000)->at(3)->mini(0)->maxi(255);

        add(mem_t{255, 000, 000, 000, 255, 000, 255, 255, 000, 255, 255, 000, 255, 255, 000, 255, 255}); // 02 Blue cyan turn
            mem->mod(new K32_mod_sinus)->period(10000)->at(6)->at(7)->phase(0)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(10000)->at(9)->at(10)->phase(90)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(10000)->at(12)->at(13)->phase(180)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(10000)->at(15)->at(16)->phase(270)->mini(0)->maxi(255);

        add(mem_t{255, 000, 000, 000, 000, 255, 000, 000, 000, 255, 000, 000, 000, 255, 255, 255, 255}); // 03 RGBW

        add(mem_t{255, 000, 000, 000, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000}); // 04 GYRO 
            mem->mod(new K32_mod_pulse)->period(1000)->at(5)->at(6)->phase(0)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(1000)->at(8)->at(9)->phase(90)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(1000)->at(11)->at(12)->phase(180)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(1000)->at(14)->at(15)->phase(270)->param(1,25);
            mem->mod(new K32_mod_sawtooth)->period(4000)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5); 


        add(mem_t{255, 000, 000, 000, 000, 255, 255, 191, 255, 255, 191, 255, 255, 191, 255, 255, 191}); // 05 phare 
            mem->mod(new K32_mod_pulse)->period(5000)->at(5)->at(6)->at(7)->phase(0)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(5000)->at(8)->at(9)->at(10)->phase(90)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(5000)->at(11)->at(12)->at(13)->phase(180)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(5000)->at(14)->at(15)->at(16)->phase(270)->param(1,25);
            mem->mod(new K32_mod_sawtooth)->period(20000)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5);

        add(mem_t{255, 000, 000, 000, 000, 255, 255, 191, 255, 255, 191, 255, 255, 191, 255, 255, 191}); // 06 phare 
            mem->mod(new K32_mod_sinus)->period(10000)->at(5)->at(6)->at(7)->phase(0)->mini(-255)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(10000)->at(8)->at(9)->at(10)->phase(90)->mini(-255)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(10000)->at(11)->at(12)->at(13)->phase(180)->mini(-255)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(10000)->at(14)->at(15)->at(16)->phase(270)->mini(-255)->maxi(255);
            mem->mod(new K32_mod_sawtooth)->period(40000)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5);

        add(mem_t{255, 000, 255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 07 rgb
            mem->mod(new K32_mod_sinus)->period(5000)->at(2)->phase(0)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(5000)->at(3)->phase(120)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(5000)->at(4)->phase(240)->mini(0)->maxi(255);

        add(mem_t{255, 140, 255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 08 str w
        

        add(mem_t{000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 09 Black
    }
};