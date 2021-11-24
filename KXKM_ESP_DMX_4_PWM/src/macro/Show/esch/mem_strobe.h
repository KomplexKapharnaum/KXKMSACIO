#include <K32_presets.h>

class BankStrobe : public LBank
{
public:
    BankStrobe() : LBank(17)
    {
        //        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
        //       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4

        add(mem_t{255, 000, 000, 158, 219, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 00 bleu ciel

        add(mem_t{255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 01 bleu foncer

        add(mem_t{255, 000, 255, 224, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 02 jaune poussin

        add(mem_t{255, 000, 199, 190, 113, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 03 beige

        add(mem_t{255, 000, 133,  91,  39, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 04 marron

        add(mem_t{255, 000, 142, 212, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 05 vert clair

        add(mem_t{255, 000, 000, 154, 061, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 06 vert sapin

        add(mem_t{255, 000, 186,  99, 025, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 07 ocre

        add(mem_t{255, 000, 226, 123, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 08 orange

        add(mem_t{255, 000, 188, 052, 186, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 09 violet


        add(mem_t{255, 000, 000, 158, 219, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 00 bleu ciel
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 000, 000, 255, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 01 bleu foncer
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 255, 224, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 02 jaune poussin
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 199, 190, 113, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 03 beige
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 133,  91,  39, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 04 marron
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 142, 212, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 05 vert clair
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 000, 154, 061, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 06 vert sapin
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 186,  99, 025, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 07 ocre
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 226, 123, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 08 orange
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{255, 000, 188, 052, 186, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 09 violet
        mem->mod(new K32_mod_sinus)->period(10000)->at(0)->phase(0)->mini(127)->maxi(255);

        add(mem_t{000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 20 noir
    }
};

//         add(mem_t{255, 240, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 09 cho

//         add(mem_t{255, 200, 255, 255, 191, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000}); // 10 froid