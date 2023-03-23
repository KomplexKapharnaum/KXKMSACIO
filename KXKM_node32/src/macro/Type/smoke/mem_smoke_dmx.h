#include <K32_presets.h>

#define SMOKE_PATCHSIZE 3

class BankSmoke : public LBank { 
    public:
        BankSmoke() : LBank(SMOKE_PATCHSIZE) 
        {
//               {master ,  str,  str speed  }
                add(    0,    0,          0 ); // 00 OFF
                add(  255,  255,        255 ); // 01 ON
        }
    };
