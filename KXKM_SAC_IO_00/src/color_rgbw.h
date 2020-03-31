
void color_rgbw(int rgbw_id,int rgbw_value)
{
    int color_r , color_g , color_b , color_w;

    color_r = 0;
    color_g = 0;
    color_b = 0;
    color_w = 0;

    //////////////////////////////////// COLOR //////////////////////////////////

    if (rgbw_value < 11)
    {
        color_r = 0;
        color_g = 0;
        color_b = 0;
        color_w = 0;
    }// black
    else if (rgbw_value < 21)
    {
        color_r = 255;
        color_g = 0;
        color_b = 0;
        color_w = 0;
    }// red
    else if (rgbw_value < 31)
    {
        color_r = 0;
        color_g = 255;
        color_b = 0;
        color_w = 0;
    }// green
    else if (rgbw_value < 41)
    {
        color_r = 0;
        color_g = 0;
        color_b = 255;
        color_w = 0;
    }// blue
    else if (rgbw_value < 51)
    {
        color_r = 0;
        color_g = 0;
        color_b = 0;
        color_w = 255;
    }// white
    else if (rgbw_value < 61)
    {
        color_r = 255;
        color_g = 255;
        color_b = 0;
        color_w = 0;
    }// yelow
    else if (rgbw_value < 71)
    {
        color_r = 255;
        color_g = 0;
        color_b = 255;
        color_w = 0;
    }// magenta
    else if (rgbw_value < 81)
    {
        color_r = 0;
        color_g = 255;
        color_b = 255;
        color_w = 0;
    }// cyan
    else if (rgbw_value < 91)
    {
        color_r = 255;
        color_g = 100;
        color_b = 0;
        color_w = 0;
    }// orange

    ///////////////////////////////////// ID ///////////////////////////////////

    if (rgbw_id == 0)
    {
        tri1r = color_r;
        tri1g = color_g;
        tri1b = color_b;
        tri1w = color_w;
    }
    else if (rgbw_id == 1)
    {
        tri2r = color_r;
        tri2g = color_g;
        tri2b = color_b;
        tri2w = color_w;
    }
    else if (rgbw_id == 2)
    {
        tri3r = color_r;
        tri3g = color_g;
        tri3b = color_b;
        tri3w = color_w;
    }
    else if (rgbw_id == 3)
    {
        tri4r = color_r;
        tri4g = color_g;
        tri4b = color_b;
        tri4w = color_w;
    }

}// color_rgbw