// ANIM MAREE
//

class Anim_maree : public K32_anim
{
public:

  // Loop
  void draw(int data[ANIM_DATA_SLOTS])
  {
    int position = data[0];

    for (int k=0; k<=size(); k++) 
    {
      if (k >= position) this->pixel(k, CRGBW{255, 255, 255, 255}); 
      else this->pixel(k, CRGBW::Black); 
    }

  }
};