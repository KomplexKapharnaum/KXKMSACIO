#define NUMBER_OF_MEM  11
int MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // BLACK
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // external
  {255    , 0  , 0  , 0  , 255, 0      , 0        , 0       , 0       , 0         , 90     , 90     , 90     , 90     , 0         , 0          , 255  , 0   , 0   },  // white
  {255    , 255, 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 90     , 0      , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Red
  {255    , 0  , 255, 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 90     , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Green
  {255    , 0  , 0  , 255, 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 90     , 0      , 0         , 0          , 255  , 0   , 0   },  // Blue
  {255    , 255, 255, 0  , 0  , 0      , 0        , 0       , 0       , 0         , 100    , 100    , 0      , 0      , 0         , 0          , 255  , 0   , 0   },  // Yellow
  {255    , 0  , 255, 255, 0  , 0      , 0        , 0       , 0       , 0         , 0      , 100    , 100    , 0      , 0         , 0          , 255  , 0   , 0   },  // Cyan
  {255    , 255, 0  , 255, 0  , 0      , 0        , 0       , 0       , 0         , 110    , 0      , 110    , 0      , 0         , 0          , 255  , 0   , 0   },  // Magenta
  {255    , 255, 255, 255, 0  , 0      , 255      , 127     , 0       , 0         , 0      , 255    , 0      , 0      , 15        , 0          , 255  , 0   , 0   },  // arc
  {255    , 255, 255, 255, 255, 0      , 0        , 0       , 11      , 80        , 110    , 110    , 110    , 110    , 0         , 0          , 255  , 0   , 0   }   // str white
};
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , color_mod , mirror_mod , zoom , pw1 , pw2 }
int MEM_PREV[NUMBER_OF_MEM][24] = {
  { 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // BLACK
  { 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // external
  { 0   , 0   , 0   , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // white
  { 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // Red
  { 0   , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // Green
  { 0   , 0   , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // Blue
  { 30  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // Yellow
  { 0   , 30  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // Cyan
  { 30  , 0   , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0 }, // Magenta
  { 30  , 0   , 0   , 0   , 30  , 30  , 0   , 0   , 0   , 30  , 0   , 0   , 0   , 30  , 30  , 0   , 0   , 0   , 30  , 0   , 30  , 0   , 30  , 0 }, // Arc
  { 0   , 0   , 0   , 50  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 50  , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 50  , 0   , 0   , 0   , 0 }  // str white
};
//{ r1  , g1  , b1  , w1  , r2  , g2  , b2  , w2  , r3  , g3  , w3  , w3  , r4  , g4  , b4  , w4  , r5  , g5  , b5  , w5  , r6  , g6  , b6  , w6  }                      ,             
void manu_frame(int mem) {
  
  mem = mem % NUMBER_OF_MEM;
  // Serial.print("Mem ");
  // Serial.println(mem);

  const int frameSize = adr + LULU_PATCHSIZE;
  uint8_t fakeframe[frameSize];
int p=0;
  for (int i = NUM_LEDS_PER_STRIP_max + 9 ; i < NUM_LEDS_PER_STRIP_max + 15 ; i++) {
        strands[1]->pixels[i] = pixelFromRGBW((MEM_PREV[mem][p]),(MEM_PREV[mem][p+1]),(MEM_PREV[mem][p+2]),(MEM_PREV[mem][p+3]));
        p = p + 4 ;
      }

  for (int i = 0 ; i < LULU_PATCHSIZE; i++) fakeframe[adr + i - 1] = MEM[mem][i];
  onDmxFrame(LULU_uni, adr + LULU_PATCHSIZE, 0, fakeframe);
}