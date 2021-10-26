#include <K32_presets.h>

class BankStrobe : public LBank
{
public:
    BankStrobe() : LBank(17)
    {
        //        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
        //       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4

        add(mem_t{255, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 00 Red

        add(mem_t{255, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 01 Green sinus
        mem->mod(new K32_mod_sinus)->at(0)->mini(0)->maxi(255);

        add(mem_t{255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 02 Blue

        add(mem_t{255, 000, 000, 000, 000, 255, 000, 000, 000, 255, 000, 000, 000, 255, 255, 255, 255}); // 03 RGBW

        add(mem_t{255, 000, 000, 000, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000, 255, 127, 000}); // 04 GYRO 
        mem->mod(new K32_mod_pulse)->period(8500)->at(5)->at(6)->phase(0)->param(1,25);
        mem->mod(new K32_mod_pulse)->period(8500)->at(8)->at(9)->phase(90)->param(1,25);
        mem->mod(new K32_mod_pulse)->period(8500)->at(11)->at(12)->phase(180)->param(1,25);
        mem->mod(new K32_mod_pulse)->period(8500)->at(14)->at(15)->phase(270)->param(1,25);

        add(mem_t{000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 05 Black
    }
};