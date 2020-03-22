
void do_effet_0()
{
  if (pix_mod >= 0 && pix_mod <= 10)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      pi_n_1_r[i] = pi_1_r[i];
      pi_n_1_g[i] = pi_1_g[i];
      pi_n_1_b[i] = pi_1_b[i];
      pi_n_1_w[i] = pi_1_w[i];

    } //for i
  }   //pix_mod 0

  else if (pix_mod >= 11 && pix_mod <= 20)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        pi_n_1_r[i] = pi_1_r[i];
        pi_n_1_g[i] = pi_1_g[i];
        pi_n_1_b[i] = pi_1_b[i];
        pi_n_1_w[i] = pi_1_w[i];
      }
      else
      {
        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 10

  else if (pix_mod >= 21 && pix_mod <= 30)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if ((((i + pix_pos) / (pix_start + 2)) % 2) == 0)
      {
        pi_n_1_r[i] = pi_1_r[i];
        pi_n_1_g[i] = pi_1_g[i];
        pi_n_1_b[i] = pi_1_b[i];
        pi_n_1_w[i] = pi_1_w[i];
      }
      else
      {
        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 20

  else if (pix_mod >= 31 && pix_mod <= 40)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        if (pix_start <= 1)
        {
          pix_start_v = 1;
        }
        else
        {
          pix_start_v = pix_start;
        }
        pix_coefi = (((i - pix_pos) * 100) / pix_start_v) * 0.01;
        pix_coef = pix_coefi * pix_coefi;

        pi_n_1_r[i] = pi_1_r[i] * pix_coef;
        pi_n_1_g[i] = pi_1_g[i] * pix_coef;
        pi_n_1_b[i] = pi_1_b[i] * pix_coef;
        pi_n_1_w[i] = pi_1_w[i] * pix_coef;
      }
      else
      {

        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 30

  else if (pix_mod >= 41 && pix_mod <= 50)
  {
    ref_pix_pos = (pix_start + pix_pos);
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        if (pix_start <= 1)
        {
          pix_start_v = 1;
        }
        else
        {
          pix_start_v = pix_start;
        }
        pix_coefi = (((pix_pos - ref_pix_pos) * 100) / pix_start_v) * 0.01;
        pix_coef = pix_coefi * pix_coefi;
        ref_pix_pos--;

        pi_n_1_r[i] = pi_1_r[i] * pix_coef;
        pi_n_1_g[i] = pi_1_g[i] * pix_coef;
        pi_n_1_b[i] = pi_1_b[i] * pix_coef;
        pi_n_1_w[i] = pi_1_w[i] * pix_coef;
      }
      else
      {

        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 40

  else if (pix_mod >= 51 && pix_mod <= 60)
  {
    ref_pix_pos = (pix_start + pix_pos);
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        if (pix_start <= 1)
        {
          pix_start_v = 1;
        }
        else
        {
          pix_start_v = pix_start;
        }
        if (i <= pix_center)
        {
          pix_coefi = ((((i - pix_pos + 1)) * 200) / pix_start_v) * 0.01;
          pix_coef = pix_coefi * pix_coefi;
        }
        else if (i >= pix_center)
        {
          pix_coefi = ((((pix_pos - ref_pix_pos)) * 100) / pix_start_v) * 0.01;
          pix_coef = pix_coefi * pix_coefi;
          ref_pix_pos = ref_pix_pos - 2;
        }
        if (pix_coef > 1)
          pix_coef = 1;

        pi_n_1_r[i] = pi_1_r[i] * pix_coef;
        pi_n_1_g[i] = pi_1_g[i] * pix_coef;
        pi_n_1_b[i] = pi_1_b[i] * pix_coef;
        pi_n_1_w[i] = pi_1_w[i] * pix_coef;
      }
      else
      {

        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 50

  else if (pix_mod >= 91 && pix_mod <= 100)
  {
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        if (pix_start <= 1)
        {
          pix_start_v = 1;
        }
        else
        {
          pix_start_v = pix_start;
        }
        pix_coefi = (((i - pix_pos) * 100) / pix_start_v) * 0.01;
        pix_coef = pix_coefi * pix_coefi;
        pix_coefi_fond = map((pix_coef * 100), 0, 100, 100, 0);
        pix_coef_fond = pix_coefi_fond / 100;

        pi_n_1_r[i] = (pi_1_r[i] * pix_coef) + (pi_1_sr[i] * pix_coef_fond);
        pi_n_1_g[i] = (pi_1_g[i] * pix_coef) + (pi_1_sg[i] * pix_coef_fond);
        pi_n_1_b[i] = (pi_1_b[i] * pix_coef) + (pi_1_sb[i] * pix_coef_fond);
        pi_n_1_w[i] = (pi_1_w[i] * pix_coef) + (pi_1_sw[i] * pix_coef_fond);
      }
      else
      {

        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 90

  else if (pix_mod >= 101 && pix_mod <= 110)
  {
    ref_pix_pos = (pix_start + pix_pos);
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        if (pix_start <= 1)
        {
          pix_start_v = 1;
        }
        else
        {
          pix_start_v = pix_start;
        }
        pix_coefi = (((pix_pos - ref_pix_pos) * 100) / pix_start_v) * 0.01;
        pix_coef = pix_coefi * pix_coefi;
        pix_coefi_fond = map((pix_coef * 100), 0, 100, 100, 0);
        pix_coef_fond = pix_coefi_fond / 100;
        ref_pix_pos--;

        pi_n_1_r[i] = (pi_1_r[i] * pix_coef) + (pi_1_sr[i] * pix_coef_fond);
        pi_n_1_g[i] = (pi_1_g[i] * pix_coef) + (pi_1_sg[i] * pix_coef_fond);
        pi_n_1_b[i] = (pi_1_b[i] * pix_coef) + (pi_1_sb[i] * pix_coef_fond);
        pi_n_1_w[i] = (pi_1_w[i] * pix_coef) + (pi_1_sw[i] * pix_coef_fond);
      }
      else
      {

        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 100

  else if (pix_mod >= 111 && pix_mod <= 120)
  {
    ref_pix_pos = (pix_start + pix_pos);
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= (pix_pos) && i <= pix_start + (pix_pos))
      {
        if (pix_start <= 1)
        {
          pix_start_v = 1;
        }
        else
        {
          pix_start_v = pix_start;
        }
        if (i <= pix_center)
        {
          pix_coefi = ((((i - pix_pos + 1)) * 200) / pix_start_v) * 0.01;
          pix_coef = pix_coefi * pix_coefi;
        }
        else if (i >= pix_center)
        {
          pix_coefi = ((((pix_pos - ref_pix_pos)) * 100) / pix_start_v) * 0.01;
          pix_coef = pix_coefi * pix_coefi;
          ref_pix_pos = ref_pix_pos - 2;
        }
        if (pix_coef > 1)
          pix_coef = 1;

        pix_coefi_fond = map((pix_coef * 100), 0, 100, 100, 0);
        pix_coef_fond = pix_coefi_fond / 100;

        pi_n_1_r[i] = (pi_1_r[i] * pix_coef) + (pi_1_sr[i] * pix_coef_fond);
        pi_n_1_g[i] = (pi_1_g[i] * pix_coef) + (pi_1_sg[i] * pix_coef_fond);
        pi_n_1_b[i] = (pi_1_b[i] * pix_coef) + (pi_1_sb[i] * pix_coef_fond);
        pi_n_1_w[i] = (pi_1_w[i] * pix_coef) + (pi_1_sw[i] * pix_coef_fond);
      }
      else
      {

        pi_n_1_r[i] = pi_1_sr[i];
        pi_n_1_g[i] = pi_1_sg[i];
        pi_n_1_b[i] = pi_1_sb[i];
        pi_n_1_w[i] = pi_1_sw[i];
      }
    } //for i
  }   //pix_mod 110

  else if (pix_mod >= 231 && pix_mod <= 240)
  {

    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= pix_pos && i < (rap_tri / 3) + pix_pos)
      {
        pi_n_1_r[i] = tri1r;
        pi_n_1_g[i] = tri1g;
        pi_n_1_b[i] = tri1b;
        pi_n_1_w[i] = tri1w;
      }
      else if (i >= (rap_tri / 3) + pix_pos && i < ((rap_tri / 3) * 2) + pix_pos)
      {
        pi_n_1_r[i] = tri2r;
        pi_n_1_g[i] = tri2g;
        pi_n_1_b[i] = tri2b;
        pi_n_1_w[i] = tri2w;
      }
      else if (i >= ((rap_tri / 3) * 2) + pix_pos && i < (rap_tri + pix_pos))
      {
        pi_n_1_r[i] = tri3r;
        pi_n_1_g[i] = tri3g;
        pi_n_1_b[i] = tri3b;
        pi_n_1_w[i] = tri3w;
      }
      else
      {
        pi_n_1_r[i] = 0;
        pi_n_1_g[i] = 0;
        pi_n_1_b[i] = 0;
        pi_n_1_w[i] = 0; 
      }
    }

  } //pix_mod 231

  else if (pix_mod >= 241 && pix_mod <= 250)
  {

    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
    {
      if (i >= pix_pos && i < (NUM_LEDS_PER_STRIP / 4) + pix_pos)
      {
        pi_n_1_r[i] = tri1r;
        pi_n_1_g[i] = tri1g;
        pi_n_1_b[i] = tri1b;
        pi_n_1_w[i] = tri1w;
      }
      else if (i >= (NUM_LEDS_PER_STRIP / 4) + pix_pos && i < ((NUM_LEDS_PER_STRIP / 4) * 2) + pix_pos)
      {
        pi_n_1_r[i] = tri2r;
        pi_n_1_g[i] = tri2g;
        pi_n_1_b[i] = tri2b;
        pi_n_1_w[i] = tri2w;
      }
      else if (i >= ((NUM_LEDS_PER_STRIP / 4) * 2) + pix_pos && i < ((NUM_LEDS_PER_STRIP / 4) * 3) + pix_pos)
      {
        pi_n_1_r[i] = tri3r;
        pi_n_1_g[i] = tri3g;
        pi_n_1_b[i] = tri3b;
        pi_n_1_w[i] = tri3w;
      }
      else
      {
        pi_n_1_r[i] = tri4r;
        pi_n_1_g[i] = tri4g;
        pi_n_1_b[i] = tri4b;
        pi_n_1_w[i] = tri4w;
      }
    }

  } //pix_mod 241

} // do_effet_0