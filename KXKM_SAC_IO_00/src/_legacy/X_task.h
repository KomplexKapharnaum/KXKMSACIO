void Map1code(void *pvParameters)
{
  //void Map1code() {
  while (1)
  {
    // color mode
    if (color_mode >= 0 && color_mode <= 10)
    {
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
      {
        pi_1_r[i] = rr;
        pi_1_g[i] = gg;
        pi_1_b[i] = bb;
        pi_1_w[i] = ww;

        pi_1_sr[i] = srr;
        pi_1_sg[i] = sgg;
        pi_1_sb[i] = sbb;
        pi_1_sw[i] = sww;

      } // for i
    }
    else if (color_mode >= 11 && color_mode <= 20)
    {
      float P_S = start_color;
      float P_E = end_color;
      float P_S_E;
      float P_S_N;

      for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
      {
        if (P_S < P_E)
        {
          P_S_E = P_E - P_S;
          P_S_N = P_S + ((P_S_E / NUM_LEDS_PER_STRIP) * i);
        }
        else if (P_S > P_E)
        {
          P_S_E = P_S - P_E;
          P_S_N = P_E + ((P_S_E / NUM_LEDS_PER_STRIP) * i);
        }
        else
        {
          P_S_E = P_S;
          P_S_N = P_S + ((P_S_E / NUM_LEDS_PER_STRIP) * i);
        }

        if (P_S_N >= 0 && P_S_N < 42.5)
        {
          rrr = map(P_S_N, 0, 42.5, 255, 255);
          ggg = map(P_S_N, 0, 42.5, 0, 255);
          bbb = map(P_S_N, 0, 42.5, 0, 0);
        }
        else if (P_S_N >= 42.5 && P_S_N < 85)
        {
          rrr = map(P_S_N, 42.5, 85, 255, 0);
          ggg = map(P_S_N, 42.5, 85, 255, 255);
          bbb = map(P_S_N, 42.5, 85, 0, 0);
        }
        else if (P_S_N >= 85 && P_S_N < 127.5)
        {
          rrr = map(P_S_N, 85, 127.5, 0, 0);
          ggg = map(P_S_N, 85, 127.5, 255, 255);
          bbb = map(P_S_N, 85, 127.5, 0, 255);
        }
        else if (P_S_N >= 127.5 && P_S_N < 170)
        {
          rrr = map(P_S_N, 127.5, 170, 0, 0);
          ggg = map(P_S_N, 127.5, 170, 255, 0);
          bbb = map(P_S_N, 127.5, 170, 255, 255);
        }
        else if (P_S_N >= 170 && P_S_N < 212.5)
        {
          rrr = map(P_S_N, 170, 212.5, 0, 255);
          ggg = map(P_S_N, 170, 212.5, 0, 0);
          bbb = map(P_S_N, 170, 212.5, 255, 255);
        }
        else if (P_S_N >= 212.5 && P_S_N <= 255)
        {
          rrr = map(P_S_N, 212.5, 255, 255, 255);
          ggg = map(P_S_N, 212.5, 255, 0, 0);
          bbb = map(P_S_N, 212.5, 255, 255, 0);
        }

        www = 0;

        int ci = pix_pos + i;
        if (ci >= NUM_LEDS_PER_STRIP)
        {
          ci = ci - NUM_LEDS_PER_STRIP;
        }
        else if (ci < 0)
        {
          ci = ci + NUM_LEDS_PER_STRIP;
        }

        if (ci >= 0)
        {
          if (ci <= N_L_P_S)
          {
            pi_1_r[ci] = (rrr * rr) / 255;
            pi_1_g[ci] = (ggg * gg) / 255;
            pi_1_b[ci] = (bbb * bb) / 255;
            pi_1_w[ci] = 0;
            pi_1_sr[ci] = 0;
            pi_1_sg[ci] = 0;
            pi_1_sb[ci] = 0;
            pi_1_sw[ci] = 0;
          }
          else
          {
            pi_1_r[ci] = 0;
            pi_1_g[ci] = 0;
            pi_1_b[ci] = 0;
            pi_1_w[ci] = 0;
            pi_1_sr[ci] = 0;
            pi_1_sg[ci] = 0;
            pi_1_sb[ci] = 0;
            pi_1_sw[ci] = 0;
          }
        }

      } //for (i = 0 ; i < NUM_LEDS_PER_STRIP ; i++)
    }   //(color_mode >= 11 && color_mode <= 20)
    else if (color_mode >= 21 && color_mode <= 30)
    {
      File jpgFile = SD.open(k32->samplerjpeg->path(start_color, end_color), FILE_READ);
      if (JpegDec.decodeSdFile(k32->samplerjpeg->path(start_color, end_color)))
      {
        uint32_t mcuPixels = JpegDec.MCUWidth * JpegDec.MCUHeight;
        int ci = 0;

        while (JpegDec.read())
        {
          uint16_t *pImg = JpegDec.pImage;
          for (uint8_t i = 0; i < mcuPixels; i++)
          {
            // Extract the red, green, blue values from each pixel
            uint8_t jpeg_b = uint8_t((*pImg & 0x001F) << 3);   // 5 LSB for blue
            uint8_t jpeg_g = uint8_t((*pImg & 0x07C0) >> 3);   // 6 'middle' bits for green
            uint8_t jpeg_r = uint8_t((*pImg++ & 0xF800) >> 8); // 5 MSB for red

            // if (ligne_mod >= 0 && ligne_mod <= 10) // horizon
            // {

            if (JpegDec.MCUy == ligne / 8)
            {
              if (i >= ((ligne % 8) * 8) && i <= ((ligne % 8) * 8) + 7)
              {
                ci++;

                if (ci <= NUM_LEDS_PER_STRIP)
                {
                  pi_1_r[ci] = (jpeg_r * rr) / 255;
                  pi_1_g[ci] = (jpeg_g * gg) / 255;
                  pi_1_b[ci] = (jpeg_b * bb) / 255;
                  pi_1_w[ci] = 0;
                  pi_1_sr[ci] = 0;
                  pi_1_sg[ci] = 0;
                  pi_1_sb[ci] = 0;
                  pi_1_sw[ci] = 0;

                  // LOGINL(i);
                  // LOGINL(" ligne = ");
                  // LOGINL(ligne);
                  // LOGINL(" width = ");
                  // LOGINL(JpegDec.width);
                  // LOGINL(" height = ");
                  // LOGINL(JpegDec.height);
                  // LOGINL(" comps = ");
                  // LOGINL(JpegDec.comps);
                  // LOGINL(" MCUSPerRow = ");
                  // LOGINL(JpegDec.MCUSPerRow);
                  // LOGINL(" MCUSPerCol = ");
                  // LOGINL(JpegDec.MCUSPerCol);
                  // LOGINL(" MCUWidth = ");
                  // LOGINL(JpegDec.MCUWidth);
                  // LOGINL(" MCUHeight = ");
                  // LOGINL(JpegDec.MCUHeight);
                  // LOGINL(" MCUx = ");
                  // LOGINL(JpegDec.MCUx);
                  // LOGINL(" MCUy= ");
                  // LOGINL(JpegDec.MCUy);

                  // LOGINL(" mcupix = ");
                  // LOGINL(mcuPixels);
                  // LOGINL(" ci = ");
                  // LOGINL(ci);
                  // LOGINL(" r = ");
                  // LOGINL(jpeg_r);
                  // LOGINL(" g = ");
                  // LOGINL(jpeg_g);
                  // LOGINL(" b = ");
                  // LOGINL(jpeg_b);
                  // LOG(" ");
                }
              }
            }
            else if (JpegDec.MCUy > ligne / 8)
            {
              JpegDec.abort();
            }
            // else if (ligne_mod >= 11 && ligne_mod >= 20) // vertical
            // {
            // }
            // JpegDec.abort();
            // }
          }
        } //while
      }   //if JpegDec.decodeSdFile
    }     //(color_mode >= 21 && color_mode <= 30)
  }       //while
} //Map1code

void effTask(void *pvParameters)
{
  while (1)
  {
    do_effet_0();
    leds_show();
    yield(); // rend la main
  }
} //effTask