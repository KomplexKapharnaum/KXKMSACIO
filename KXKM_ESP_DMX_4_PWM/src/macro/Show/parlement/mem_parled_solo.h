#ifndef mem_parled_parlement_solo_h
#define mem_parled_parlement_solo_h

#define PAR_PATCHSIZE 5

class BankPar : public LBank
{
public:
    BankPar () : LBank(PAR_PATCHSIZE)
    {
        //    {0      , 1  , 2  , 3  , 4  } adr + -1
        //    {master , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str,   m , r  , g  , b  , str, }
   
        add(mem_t{  255,   0,   0, 255,   0}); // 00 blue

        add(mem_t{  255,   0,   0, 255,   0}); // 01 blue

        add(mem_t{  255,   0,   0, 255,   0}); // 02 blue
        
        add(mem_t{  255,   0,   0, 255,   0}); // 03 blue

        add(mem_t{  255,   0,   0, 255,   0}); // 04 blue

        add(mem_t{  255,   0,   0, 255,   0}); // 05 blue
        
        add(mem_t{  255, 255, 255, 255,   0}); // 06 white

        add(mem_t{  255, 255,   0,   0,   0}); // 07 red breath
            mem->mod(new K32_mod_sinus)->at(0)->period(2000);

        add(mem_t{  255, 255,   0,   0,   0}); // 08 red breath leader
            mem->mod(new K32_mod_sinus)->at(0)->period(2000);

        add(mem_t{    0,   0,   0,   0,   0}); // 09 stop -> black
    }
};


#endif