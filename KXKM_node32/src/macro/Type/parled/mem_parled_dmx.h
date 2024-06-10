#include <K32_presets.h>

class BankPar : public LBank
{
public:
    BankPar() : LBank(5)
    {
        //{master , r  , g  , b  , str }
        //{0      , 1  , 2  , 3  , 4  } adr + -1
        //
        add(255, 255, 0, 0, 0),       // 00 Red
        add(255, 0, 255, 0, 0),       // 01 Green
        add(255, 0, 0, 255, 0),       // 02 Blue
        add(255, 255, 255, 255, 0),   // 03 White
        add(255, 255, 255, 255, 0),   // 04 rvb **3 4 5**
        add(255, 255, 255, 255, 29),  // 05 str rnd 67
        add(255, 255, 255, 255, 58),  // 06 str all 67
        add(255, 255, 255, 255, 100), // 07 str all 42
        add(255, 255, 255, 255, 230), // 08 str all lent
        add(255, 255, 255, 255, 0),   // 09 circule w **9** 20>255
        add(255, 255, 255, 255, 0),   // 10 circus w b **7** 1>255
        add(255, 255, 255, 255, 89),  // 11 str w -> blue
        add(255, 255, 255, 255, 10),  // 12 color form
        add(255, 0, 127, 255, 0),     // 13 blue parcielle
        add(255, 0, 80, 200, 0),      // 14 respi blue **0**38 > 217
        add(0, 0, 0, 0, 0),           // 15 BLACK stm leave lset mem

        nowifi(255, 127, 12, 92, 0);
    }
};