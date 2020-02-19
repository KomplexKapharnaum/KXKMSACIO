#define NUMBER_OF_MEM  11
#define COEF_PREVUE 5
int MEM[NUMBER_OF_MEM][LULU_PATCHSIZE] = {
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // BLACK
  {0      , 0  , 0  , 0  , 0  , 0      , 0        , 0       , 0       , 0         , 0      , 0      , 0      , 0      , 0         , 0          , 0    , 0   , 0   },  // external
  {255    , 255, 255, 255, 255, 0      , 0        , 0       , 0       , 0         , 90     , 90     , 90     , 90     , 0         , 0          , 255  , 0   , 0   },  // str white
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

void manu_frame(int mem) {
  
  mem = mem % NUMBER_OF_MEM;
  // Serial.print("Mem ");
  // Serial.println(mem);

  const int frameSize = adr + LULU_PATCHSIZE;
  uint8_t fakeframe[frameSize];

  for (int i = NUM_LEDS_PER_STRIP_max + 9 ; i < NUM_LEDS_PER_STRIP_max + 12 ; i++) {
        strands[1]->pixels[i] = pixelFromRGBW((MEM[mem][1]/COEF_PREVUE),(MEM[mem][2]/COEF_PREVUE),(MEM[mem][3]/COEF_PREVUE),(MEM[mem][4]/COEF_PREVUE));
      }
  for (int i = NUM_LEDS_PER_STRIP_max + 12 ; i < NUM_LEDS_PER_STRIP_max + 15 ; i++) {
        strands[1]->pixels[i] = pixelFromRGBW((MEM[mem][10]/COEF_PREVUE),(MEM[mem][11]/COEF_PREVUE),(MEM[mem][12]/COEF_PREVUE),(MEM[mem][13]/COEF_PREVUE));
      }
  
  for (int i = 0 ; i < LULU_PATCHSIZE; i++) fakeframe[adr + i - 1] = MEM[mem][i];
  onDmxFrame(LULU_uni, adr + LULU_PATCHSIZE, 0, fakeframe);
}