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

        add(mem_t{255, 000, 000, 000, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000}); // 03 GYRO odd even
            mem->mod(new K32_mod_sawtooth)->period(500)->at(ANIM_ROUTE)->absolute()->mini(9)->maxi(11); 

        add(mem_t{255, 000, 000, 000, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000}); // 04 GYRO fixture
            mem->mod(new K32_mod_sawtooth)->period(500)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5);

        add(mem_t{255, 000, 000, 000, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000}); // 05 GYRO 
            mem->mod(new K32_mod_pulse)->period(500)->at(5)->at(6)->phase(0)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(500)->at(8)->at(9)->phase(90)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(500)->at(11)->at(12)->phase(180)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(500)->at(14)->at(15)->phase(270)->param(1,25);
            mem->mod(new K32_mod_sawtooth)->period(2000)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5); 


        add(mem_t{255, 000, 000, 000, 000, 255, 255, 191, 255, 255, 191, 255, 255, 191, 255, 255, 191}); // 06 phare 
            mem->mod(new K32_mod_pulse)->period(2500)->at(5)->at(6)->at(7)->phase(0)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(2500)->at(8)->at(9)->at(10)->phase(90)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(2500)->at(11)->at(12)->at(13)->phase(180)->param(1,25);
            mem->mod(new K32_mod_pulse)->period(2500)->at(14)->at(15)->at(16)->phase(270)->param(1,25);
            mem->mod(new K32_mod_sawtooth)->period(10000)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5);

        // add(mem_t{255, 000, 000, 000, 000, 255, 255, 191, 255, 255, 191, 255, 255, 191, 255, 255, 191}); // 06 phare 
        //     mem->mod(new K32_mod_sinus)->period(10000)->at(5)->at(6)->at(7)->phase(0)->mini(-255)->maxi(255);
        //     mem->mod(new K32_mod_sinus)->period(10000)->at(8)->at(9)->at(10)->phase(72)->mini(-255)->maxi(255);
        //     mem->mod(new K32_mod_sinus)->period(10000)->at(11)->at(12)->at(13)->phase(144)->mini(-255)->maxi(255);
        //     mem->mod(new K32_mod_sinus)->period(10000)->at(14)->at(15)->at(16)->phase(216)->mini(-255)->maxi(255);
        //     mem->mod(new K32_mod_pulse)->period(10000)->param(1,80)
        //                                                 ->mini(-255)->maxi(255)  
        //                                                 ->at(5)->at(6)->at(7)
        //                                                 ->at(8)->at(9)->at(10)
        //                                                 ->at(11)->at(12)->at(13)
        //                                                 ->at(14)->at(15)->at(16);
        //     mem->mod(new K32_mod_sawtooth)->period(40000)->at(ANIM_ROUTE)->absolute()->mini(1)->maxi(5);
        add(mem_t{255, 000, 255, 191, 150, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 07 w cho

        add(mem_t{255, 000, 255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 08 w froid




        add(mem_t{255, 240, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 09 str w

        add(mem_t{255, 200, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 10 str w
        
        add(mem_t{255, 000, 255, 255, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 11 rgb
            mem->mod(new K32_mod_sinus)->period(5000)->at(2)->phase(0)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(5000)->at(3)->phase(120)->mini(0)->maxi(255);
            mem->mod(new K32_mod_sinus)->period(5000)->at(4)->phase(240)->mini(0)->maxi(255);

        add(mem_t{000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 10 Black
    }
};