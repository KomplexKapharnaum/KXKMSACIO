#ifndef mem_parled_parlement_solo_h
#define mem_parled_parlement_solo_h

class BankPar : public LBank
{
public:
    BankPar () : LBank(5)
    {
        //    {0      , 1  , 2  , 3  , 4  } adr + -1
        //    {master , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str, }
   
       add(mem_t{  255,   0,   0, 255,   0}); // 00 all blue
       add(mem_t{  255, 255, 255, 255,   0}); // 01 1 white other blue
       add(mem_t{  255,   0,   0, 255,   0}); // 02 2 white other blue
       add(mem_t{  255,   0,   0, 255,   0}); // 03 3 white other blue
       add(mem_t{  255,   0,   0, 255,   0}); // 04 4 white other blue
       add(mem_t{  255,   0,   0, 255,   0}); // 05 5 white other blue
       add(mem_t{  255, 255, 255, 255,   0}); // 06 all white
       add(mem_t{  255, 255, 255, 255,  89}); // 07 str all speed white
       add(mem_t{  255, 255, 255, 255,  30}); // 08 str all lent white
       add(mem_t{  255, 255,   0,   0,   0}); // 09 all red
       add(mem_t{  255,   0, 255,   0,   0}); // 10 all green
       add(mem_t{  255,   0, 255, 255,   0}); // 11 all cyan
       add(mem_t{  255, 255,   0, 255,   0}); // 12 all magenta
       add(mem_t{  255, 255, 255,   0,   0}); // 13 all yellow
       add(mem_t{  255, 255, 127,   0,   0}); // 14 all orange
       add(mem_t{    0,   0,   0,   0,   0}); // 15 BLACK stm leave lset mem

    }
};


#endif