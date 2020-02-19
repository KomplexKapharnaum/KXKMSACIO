#define NUMBER_OF_MEM  10

int MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // BLACK
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // external
  {255    , 255, 255, 255, 255, 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // str white
  {255    , 255, 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Red
  {255    , 0  , 255, 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Green
  {255    , 0  , 0  , 255, 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Blue
  {255    , 255, 255, 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Yellow
  {255    , 0  , 255, 255, 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // 
  {255    , 255, 0  , 255, 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },   // 
  {255    , 255, 255, 255, 255, 0      , 0        , 0       , 11      , 80        , 0      , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   }  // str white
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , color_mod , mirror_mod , zoom , pw1 , pw2 }

void manu_frame(int mem) {
  
  mem = mem % NUMBER_OF_MEM;
  // Serial.print("Mem ");
  // Serial.println(mem);

  const int frameSize = adr + LULU_PATCHSIZE;
  uint8_t fakeframe[frameSize];
  
  for (int i = 0 ; i < LULU_PATCHSIZE; i++) fakeframe[adr + i - 1] = MEM[mem][i];
  onDmxFrame(LULU_uni, adr + LULU_PATCHSIZE, 0, fakeframe);
}