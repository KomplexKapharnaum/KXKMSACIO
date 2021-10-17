#include <K32_presets.h>

class BankPWM : LBank <4> { 
    public:
        BankPWM() {

            add(mem_t {  255,  255,  255,  255});   // 00 

            add(mem_t {  170,  170,  170,  170});   // 01 

            add(mem_t {  126,  126,  126,  126});   // 02 

            add(mem_t {   82,   82,   82,   82});   // 03 

            add(mem_t {  255,  255,  255,  255})    // 04
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_sinus)->at(1)->at(5)->at(8)->at(3)->at(7)->at(2)->at(6)->period(8500)->phase(0)->mini(-50)->maxi(255);
                });

            add(mem_t {    0,    0,    0,    0});   // 05 

            add(mem_t {  255,  170,  126,   82})    // 06
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_pulse)->at(1)->at(2)->at(3)->at(7)->at(8)->at(6)->at(5)->param(1, 10)->period(500);
                });

            add(mem_t {  170,  126,   82,    0});   // 07 

            add(mem_t {  126,   82,    0,  255});   // 08 

            add(mem_t {   82,    0,  255,  170})    // 09
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_sinus)->at(0)->mini(100)->maxi(255)->period(2000);
                });

            add(mem_t {    0,  255,  170,  126})    // 10
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_sinus)->at(1)->at(2)->period(8500)->phase(0)->mini(0)->maxi(255);
                });

            add(mem_t {  170,  126,   82,    0})    // 11
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_pulse)->at(2)->at(3)->param(1, 100)->period(7000);
                });

            add(mem_t {  255,  170,  126,   82})    // 12
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_sinus)->at(1)->period(8500)->phase(0)->mini(0)->maxi(255);
                    anim->mod(new K32_mod_sinus)->at(2)->period(8500)->phase(120)->mini(0)->maxi(255);
                    anim->mod(new K32_mod_sinus)->at(3)->period(8500)->phase(240)->mini(0)->maxi(255);
                });

            add(mem_t {  126,   82,    0,  255});   // 13 

            add(mem_t {   82,    0,  255,  170})    // 14
                ->onload([](K32_anim *anim){ 
                    anim->mod(new K32_mod_sinus)->at(0)->period(8500)->mini(38)->maxi(217);
                }); 

            add(mem_t {    0,    0,    0,    0});   // 15 BLACK


            nowifi(mem_t { LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER, LULU_MEMNOWIFI_MASTER});            
        }
};
