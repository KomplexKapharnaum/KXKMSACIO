#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(mem_t {    0,    0,    0,    0});   // 00 off

            add(mem_t {  255,    0,    0,    0});   // 01 on

            add(mem_t {    0,    0,    0,    0});   // 02 sablier 1m30

            add(mem_t {  255,    0,    0,    0});   // 03 red ready
                mem->mod(new K32_mod_sinus)->at(0)->period(1000);

            add(mem_t {    0,    0,    0,    0});   // 04 sablier 1m00

            add(mem_t {   0,    0,    0,    0});   // 05 sablier 0m30

            add(mem_t {    0,    0,    0,    0});   // 06

            add(mem_t {    0,    0,    0,    0});   // 07 

            add(mem_t {    0,    0,    0,    0});   // 08 

            add(mem_t {    0,    0,    0,    0});   // 09

            add(mem_t {    0,    0,    0,    0});   // 10

            add(mem_t {    0,    0,    0,    0});   // 11

            add(mem_t {    0,    0,    0,    0});   // 12

            add(mem_t {    0,    0,    0,    0});   // 13 

            add(mem_t {    0,    0,    0,    0});   // 14

            add(mem_t {    0,    0,    0,    0});   // 15 BLACK

        }
};
