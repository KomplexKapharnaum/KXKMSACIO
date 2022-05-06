#include <K32_presets.h>
#include <K32_version.h>

class BankPWM : public LBank { 
    public:
        BankPWM() : LBank(PWM_N_CHAN) {

            add(mem_t {    0,    0,    0,    0});   // 00 off

            add(mem_t {    0,    0,    0,    0});   // 01 

            add(mem_t {    0,    0,    0,    0});   // 02 

            add(mem_t {    0,    0,    0,    0});   // 03 

            add(mem_t {    0,    0,    0,    0});   // 04

            add(mem_t {    0,    0,    0,    0});   // 05 

            add(mem_t {  255,  255,  255,  255});   // 06 on

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
