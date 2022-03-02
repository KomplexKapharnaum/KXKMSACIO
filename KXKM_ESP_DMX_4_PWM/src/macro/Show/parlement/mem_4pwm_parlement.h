#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(mem_t {    0,    0,    0,    0});   // 00 off

            add(mem_t {  255,  255,  255,  255});   // 01 on

            add(mem_t {  255,    0,    0,    0});   // 02 

            add(mem_t {   82,   82,   82,   82});   // 03 

            add(mem_t {  255,  255,  255,  255});   // 04

            add(mem_t {    0,    0,    0,    0});   // 05 

            add(mem_t {  255,  170,  126,   82});   // 06

            add(mem_t {  170,  126,   82,    0});   // 07 

            add(mem_t {  126,   82,    0,  255});   // 08 

            add(mem_t {   82,    0,  255,  170});   // 09

            add(mem_t {    0,  255,  170,  126});   // 10

            add(mem_t {  170,  126,   82,    0});   // 11

            add(mem_t {  255,  170,  126,   82});   // 12

            add(mem_t {  126,   82,    0,  255});   // 13 

            add(mem_t {   82,    0,  255,  170});   // 14

            add(mem_t {    0,    0,    0,    0});   // 15 BLACK

        }
};
