#ifndef mem_parled_parlement_solo_h
#define mem_parled_parlement_solo_h

class BankPar : public LBank
{
public:
    BankPar () : LBank(5)
    {
        //    {0      , 1  , 2  , 3  , 4  } adr + -1
        //    {master , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str, }
   
        add(mem_t{  255,   0,   0, 255,   0}); // 00 blue

        add(mem_t{  255, 255, 255, 255,   0}); // 01 white

        add(mem_t{  255, 255,   0,   0,   0}); // 02 red breath
            mem->mod(new K32_mod_sinus)->at(0)->period(2000);

    }
};


#endif