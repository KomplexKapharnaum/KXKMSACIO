#include <K32_presets.h>


class BankStrobe : public LBank { 
    public:
        BankStrobe() : LBank(17) {

            add(mem_t {  255, 255,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  0});   // 00 Red

            add(mem_t {  255, 255,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  0}); // 01 Red sinus
                mem->mod(new K32_mod_sinus)->at(0)->mini(0)->maxi(255);
    
            add(mem_t {   0,    0,   0,   0,   0,       0,         0,        0,        0,          0,       0,       0,       0,       0,           0,  0});   // 02 Black
        
        }
};