#ifndef STROBE_MENU_H
#define STROBE_MENU_H

#include "preset_color_str.h"

void remote_strobe();

void draw_red_str();
void send_red_str();
void draw_green_str();
void send_green_str();
void draw_blue_str();
void send_blue_str();
void draw_color_str();
void send_color_str();
void draw_master_str();
void send_master_str();
bool color_value_str();
bool id_value_str();
bool master_value_str();
bool rgb_value_str(uint8_t rgb);

bool _mod_coarse_str = false;
bool color_front_back_str = false;
uint8_t strobe_fonction = 0;
bool esc_strobe = true;

String STROBE_MQTT_ID = "all";
String STROBE_MQTT_K32 = "k32/";

uint8_t strobe_id_fonction = 1;
String strobe_id_fonct = "CH";
String id_cal_strobe = "all";

uint8_t strobe_red, strobe_green, strobe_blue, strobe_str;
int16_t strobe_str_speed = 127;

String strobe_mqtt_frame;

int16_t strobe_Master = 255;
String strobe_Mast = String(strobe_Master);

char strobe_mqtt_topic_c[64];
String strobe_mqtt_topic;
String STROBE_MQTT_MEM = "/leds/mem";
String STROBE_MQTT_STOP = "/leds/stop";
String STROBE_MQTT_SLOWER = "/leds/modall/slower";
String STROBE_MQTT_SMALLER = "/leds/modall/smaller";
String STROBE_MQTT_FASTER = "/leds/modall/faster";
String STROBE_MQTT_BIGGER = "/leds/modall/bigger";
String STROBE_MQTT_FADE_IN = "/leds/master/fadein";
String STROBE_MQTT_FADE_OUT = "/leds/master/fadeout";
String STROBE_MQTT_MASTER = "/leds/master";
String STROBE_MQTT_FRAME = "/leds/frame";

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW RED////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_red_str()
{

    m5.lcd.setTextColor(TFT_RED);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Red : " + String(strobe_red), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND RED////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
//       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4
void send_red_str()
{
    strobe_mqtt_frame = "-1|-1|";

    strobe_mqtt_frame += String(strobe_red);
    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FRAME);
    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
    ez.mqtt32->publish(strobe_mqtt_topic_c, strobe_mqtt_frame.c_str(), 1);
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW GREEN//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_green_str()
{
    m5.lcd.setTextColor(TFT_GREEN);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Green : " + String(strobe_green), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND GREEN//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
//       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4
void send_green_str()
{
    strobe_mqtt_frame = "-1|-1|-1|";

    strobe_mqtt_frame += String(strobe_green);
    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FRAME);
    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
    ez.mqtt32->publish(strobe_mqtt_topic_c, strobe_mqtt_frame.c_str(), 1);
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW BLUE //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_blue_str()
{
    m5.lcd.setTextColor(TFT_BLUE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Blue : " + String(strobe_blue), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND BLUE///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
//       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4
void send_blue_str()
{
    strobe_mqtt_frame = "-1|-1|-1|-1|";

    strobe_mqtt_frame += String(strobe_blue);
    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FRAME);
    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
    ez.mqtt32->publish(strobe_mqtt_topic_c, strobe_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW COLOR//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_color_str()
{

    m5.lcd.setTextColor(TFT_RED);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    if (color_front_back_str)
    {
        m5.lcd.drawString("Back", TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
    }
    else
    {
        m5.lcd.drawString("Front", TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND COLOR//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//        0     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16
//       dim, stro,R1-4,G1-4,B1-4,  R1,  G1,  B1,  R2,  G2,  B2,  R3,  G3,  B3,  R4,  G4,  B4
void send_color_str()
{

    strobe_mqtt_frame = "-1|-1|";

    strobe_mqtt_frame += String(strobe_red) + "|" + String(strobe_green) + "|" + String(strobe_blue);
    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FRAME);
    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
    ez.mqtt32->publish(strobe_mqtt_topic_c, strobe_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW MASTER/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_master_str()
{
    m5.lcd.setTextColor(TFT_WHITE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Master:" + String(strobe_Master), 10, 10 + ez.theme->input_vmargin + text_h + 10);
    if (strobe_fonction == 2)
    {
        draw_color_str();
    }
    else if (strobe_fonction == 3)
    {
        draw_red_str();
    }
    else if (strobe_fonction == 4)
    {
        draw_green_str();
    }
    else if (strobe_fonction == 5)
    {
        draw_blue_str();
    }
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND MASTER/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void send_master_str()
{
    strobe_Mast = String(strobe_Master);
    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_MASTER);
    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
    ez.mqtt32->publish(strobe_mqtt_topic_c, strobe_Mast.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////COLOR_VALUE//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool color_value_str()
{
    bool r, g, b = false;
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    uint8_t color_fonction = 0;
    String color_fonct = "RED";
    int res;
    esc_strobe = true;

    msg += " Enter RED value & =";
    ez.msgBox("M5 REMOTE STROBE", msg, "## color|" + color_fonct + "###Back", false);
    draw_master_str();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        if (action == "Back")
            return false;

        if (action == "color")
        {
            color_fonction += 1;
            if (color_fonction >= 3)
            {
                color_fonction = 0;
            }
            if (color_fonction == 0)
            {
                color_fonct = "RED";
                msg = "";
                msg += " Enter RED value & =";
            }
            else if (color_fonction == 1)
            {
                color_fonct = "GREEN";
                msg = "";
                msg += " Enter GREEN value & =";
            }
            else if (color_fonction == 2)
            {
                color_fonct = "BLUE";
                msg = "";
                msg += " Enter BLUE value & =";
            }

            ez.msgBox("M5 REMOTE STROBE", msg, "## color|" + color_fonct + "###Back", false);
            draw_master_str();
        };
        res = atoi(res_value.c_str());
        // FACE
        //
        if (digitalRead(KEYBOARD_INT) == LOW)
        {
            Wire.requestFrom(KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
            while (Wire.available())
            {
                uint8_t key_val = Wire.read(); // receive a byte as character
                String value((char)key_val);

                switch ((char)key_val)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    bad = false;
                    res_value += value;
                    break;

                case '.':
                    break;
                case '=':
                    if (res < 256 && res_value != "")
                    {
                        if (color_fonction == 0)
                        {
                            strobe_red = res_value.toInt();
                            r = true;
                        }
                        else if (color_fonction == 1)
                        {
                            strobe_green = res_value.toInt();
                            g = true;
                        }
                        else if (color_fonction == 2)
                        {
                            strobe_blue = res_value.toInt();
                            b = true;
                        }

                        color_fonction += 1;
                        res_value = "";
                    }
                    else if (res_value == "")
                    {
                        if (color_fonction == 0)
                        {
                            r = true;
                        }
                        else if (color_fonction == 1)
                        {
                            g = true;
                        }
                        else if (color_fonction == 2)
                        {
                            b = true;
                        }

                        color_fonction += 1;
                        res_value = "";
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        if (color_fonction == 0)
                        {
                            color_fonct = "RED";
                            msg += " Enter RED value & =";
                            r = false;
                        }
                        else if (color_fonction == 1)
                        {
                            color_fonct = "GREEN";
                            msg += " Enter GREEN value & =";
                            g = false;
                        }
                        else if (color_fonction == 2)
                        {
                            color_fonct = "BLUE";
                            msg += " Enter BLUE value & =";
                            b = false;
                        }

                        ez.msgBox("M5 REMOTE STROBE", msg, "## color|" + color_fonct + "###Back", false);
                        draw_master_str();
                    }
                    if (r == true && g == true && b == true)
                    {
                        return true;
                    }
                    else
                    {
                        bad = true;
                        if (color_fonction >= 3)
                        {
                            color_fonction = 0;
                        }
                        if (color_fonction == 0)
                        {
                            color_fonct = "RED";
                            msg = "";
                            msg += " Enter RED value & =";
                        }
                        else if (color_fonction == 1)
                        {
                            color_fonct = "GREEN";
                            msg = "";
                            msg += " Enter GREEN value & =";
                        }
                        else if (color_fonction == 2)
                        {
                            color_fonct = "BLUE";
                            msg = "";
                            msg += " Enter BLUE value & =";
                        }

                        ez.msgBox("M5 REMOTE STROBE", msg, "## color|" + color_fonct + "###Back", false);
                        draw_master_str();
                    }
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    res_value = "";
                    if (color_fonction == 0)
                    {
                        color_fonct = "RED";
                        msg = "";
                        msg += " Enter RED value & =";
                    }
                    else if (color_fonction == 1)
                    {
                        color_fonct = "GREEN";
                        msg = "";
                        msg += " Enter GREEN value & =";
                    }
                    else if (color_fonction == 2)
                    {
                        color_fonct = "BLUE";
                        msg = "";
                        msg += " Enter BLUE value & =";
                    }

                    ez.msgBox("M5 REMOTE STROBE", msg, "## color|" + color_fonct + "###Back", false);
                    draw_master_str();
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                    ez.msgBox("M5 REMOTE STROBE", res_value, "## color|" + color_fonct + "###Back", false);
                draw_master_str();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////ID_VALUE//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

bool id_value_str()

{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";

    msg += " Enter N° CH & =";
    msg += "|0 = all";

    ez.msgBox("M5 REMOTE STROBE", msg, "## idmode|" + strobe_id_fonct + "### Back", false);
    draw_master_str();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        // BTN A/B/C
        if (action == "Back")
            return false;

        if (action == "idmode")
        {
            strobe_id_fonction += 1;
            if (strobe_id_fonction >= 3)
            {
                strobe_id_fonction = 0;
            }
            if (strobe_id_fonction == 0)
            {
                strobe_id_fonct = "ID";
                msg = "";
                msg += " Enter N° ID & =";
                msg += "|0 = all";
                ez.msgBox("M5 REMOTE STROBE", msg, "## idmode|" + strobe_id_fonct + "### Back", false);
                draw_master_str();
            }
            else if (strobe_id_fonction == 1)
            {
                strobe_id_fonct = "CH";
                msg = "";
                msg += " Enter N° CH & =";
                msg += "|0 = all";
                ez.msgBox("M5 REMOTE STROBE", msg, "## idmode|" + strobe_id_fonct + "### Back", false);
                draw_master_str();
            }
            else if (strobe_id_fonction == 2)
            {
                strobe_id_fonct = "ID Lu";
                msg = "";
                msg += " Enter N° ID Lu & =";
                msg += "|0 = all";
                ez.msgBox("M5 REMOTE STROBE", msg, "## idmode|" + strobe_id_fonct + "### Back", false);
                draw_master_str();
            }
        };
        // FACE
        //
        if (digitalRead(KEYBOARD_INT) == LOW)
        {
            Wire.requestFrom(KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
            while (Wire.available())
            {
                uint8_t key_val = Wire.read(); // receive a byte as character
                String value((char)key_val);

                switch ((char)key_val)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    bad = false;
                    res_value += value;
                    break;

                case '.':
                    break;
                case '=':
                    if (res_value == "")
                        res_value = "0";

                    if (res_value == "0")
                    {
                        STROBE_MQTT_ID = "all";
                        id_cal_strobe = "all";
                    }
                    else if (strobe_id_fonction == 0)
                    {
                        STROBE_MQTT_ID = String('e') + String(res_value);
                        id_cal_strobe = "id" + res_value;
                    }
                    else if (strobe_id_fonction == 1)
                    {
                        STROBE_MQTT_ID = String('c') + String(res_value);
                        id_cal_strobe = "ch" + res_value;
                    }
                    else if (strobe_id_fonction == 2)
                    {
                        STROBE_MQTT_ID = String('l') + String(res_value);
                        id_cal_strobe = "Lu" + res_value;
                    }
                    return true;
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    res_value = "";
                    if (strobe_id_fonction == 0)
                    {
                        strobe_id_fonct = "ID";
                        msg = "";
                        msg += " Enter N° ID & =";
                        msg += "|0 = all";
                    }
                    else if (strobe_id_fonction == 1)
                    {
                        strobe_id_fonct = "CH";
                        msg = "";
                        msg += " Enter N° CH & =";
                        msg += "|0 = all";
                    }
                    else if (strobe_id_fonction == 2)
                    {
                        strobe_id_fonct = "ID Lu";
                        msg = "";
                        msg += " Enter N° ID Lu & =";
                        msg += "|0 = all";
                    }

                    ez.msgBox("M5 REMOTE STROBE", msg, "## idmode|" + strobe_id_fonct + "### Back", false);
                    draw_master_str();
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE STROBE", res_value, "## idmode|" + strobe_id_fonct + "### Back", false);
                    draw_master_str();
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////MASTER_VALUE/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool master_value_str()
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;
    esc_strobe = true;

    msg += " Enter value to master 0 -> 255 & =";
    ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
    draw_master_str();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        if (action == "Back")
            return false;

        res = atoi(res_value.c_str());
        // FACE
        //
        if (digitalRead(KEYBOARD_INT) == LOW)
        {
            Wire.requestFrom(KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
            while (Wire.available())
            {
                uint8_t key_val = Wire.read(); // receive a byte as character
                String value((char)key_val);

                switch ((char)key_val)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (bad == true)
                        bad = false;
                    res_value += value;
                    break;

                case '.':
                    break;
                case '=':

                    if (res < 256)
                    {
                        strobe_Master = res_value.toInt();
                        send_master_str();
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to master 0 -> 255 & =";
                        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                        draw_master_str();
                    }
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    bad = true;
                    res_value = "";
                    msg = "";
                    msg += " Enter value to master 0 -> 255 & =";
                    ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                    draw_master_str();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE STROBE", res_value, "#####Back", false);
                draw_master_str();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////RGB_VALUE/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool rgb_value_str(uint8_t rgb)
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;
    esc_strobe = true;

    if (rgb == 0)
    {
        msg += " Enter value to Red 0 -> 255 & =";
        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
        draw_red_str();
    }
    else if (rgb == 1)
    {
        msg += " Enter value to Green 0 -> 255 & =";
        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
        draw_green_str();
    }
    else if (rgb == 2)
    {
        msg += " Enter value to Blue 0 -> 255 & =";
        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
        draw_blue_str();
    }

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        if (action == "Back")
            return false;

        res = atoi(res_value.c_str());
        // FACE
        //
        if (digitalRead(KEYBOARD_INT) == LOW)
        {
            Wire.requestFrom(KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
            while (Wire.available())
            {
                uint8_t key_val = Wire.read(); // receive a byte as character
                String value((char)key_val);

                switch ((char)key_val)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (bad == true)
                        bad = false;
                    res_value += value;
                    break;

                case '.':
                    break;
                case '=':

                    if (res < 256)
                    {
                        if (rgb == 0)
                        {
                            strobe_red = res_value.toInt();
                            send_red_str();
                        }
                        else if (rgb == 1)
                        {
                            strobe_green = res_value.toInt();
                            send_green_str();
                        }
                        else if (rgb == 2)
                        {
                            strobe_blue = res_value.toInt();
                            send_blue_str();
                        }

                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        if (rgb == 0)
                        {
                            msg += " Enter value to Red 0 -> 255 & =";
                            ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                            draw_red_str();
                        }
                        else if (rgb == 1)
                        {
                            msg += " Enter value to Green 0 -> 255 & =";
                            ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                            draw_green_str();
                        }
                        else if (rgb == 2)
                        {
                            msg += " Enter value to Blue 0 -> 255 & =";
                            ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                            draw_blue_str();
                        }
                    }
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    bad = true;
                    res_value = "";
                    msg = "";
                    if (rgb == 0)
                    {
                        msg += " Enter value to Red 0 -> 255 & =";
                        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                        draw_red_str();
                    }
                    else if (rgb == 1)
                    {
                        msg += " Enter value to Green 0 -> 255 & =";
                        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                        draw_green_str();
                    }
                    else if (rgb == 2)
                    {
                        msg += " Enter value to Blue 0 -> 255 & =";
                        ez.msgBox("M5 REMOTE STROBE", msg, "#####Back", false);
                        draw_blue_str();
                    }

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE STROBE", res_value, "#####Back", false);
                }
                if (rgb == 0)
                {
                    ez.msgBox("M5 REMOTE STROBE", res_value, "#####Back", false);
                    draw_red_str();
                }
                else if (rgb == 1)
                {
                    ez.msgBox("M5 REMOTE STROBE", res_value, "#####Back", false);
                    draw_green_str();
                }
                else if (rgb == 2)
                {
                    ez.msgBox("M5 REMOTE STROBE", res_value, "#####Back", false);
                    draw_blue_str();
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////REMOTE_STROBE////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void remote_strobe()
{
    uint32_t _widget_time = millis();
    uint8_t inc_value = 10;
    String action = "";
    bool _a_b = true;
    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_MEM);
    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
    String fonct = "Master";
    uint8_t page_mem = 0;
    String page_me = "0-9";

    ez.msgBox("M5 REMOTE STROBE", "Welcome", "id|" + id_cal_strobe + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
    draw_master_str();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        // Back
        if (action == "Menu")
            break;

        // ID select
        if (action == "id")
        {
            id_value_str();

            ez.msgBox("M5 REMOTE STROBE", id_cal_strobe, "id|" + id_cal_strobe + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
            draw_master_str();
        };

        if (action == "func")
        {
            strobe_fonction += 1;
            if (strobe_fonction >= 6)
            {
                strobe_fonction = 0;
            }
            if (strobe_fonction == 0)
            {
                fonct = "Master";
            }
            else if (strobe_fonction == 1)
            {
                fonct = "Speed";
            }
            else if (strobe_fonction == 2)
            {
                fonct = "Color";
            }
            else if (strobe_fonction == 3)
            {
                fonct = "Red";
            }
            else if (strobe_fonction == 4)
            {
                fonct = "Green";
            }
            else if (strobe_fonction == 5)
            {
                fonct = "Blue";
            }

            ez.msgBox("M5 REMOTE STROBE", fonct, "id|" + id_cal_strobe + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
            draw_master_str();
        };

        if (action == "page")
        {
            page_mem += 1;
            if (page_mem >= 3)
            {
                page_mem = 0;
            }
            if (page_mem == 0)
            {
                page_me = "0-9";
            }
            else if (page_mem == 1)
            {
                page_me = "10-19";
            }
            else if (page_mem == 2)
            {
                page_me = "20-29";
            }

            ez.msgBox("M5 REMOTE STROBE", page_me, "id|" + id_cal_strobe + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
            draw_master_str();
        };

        // FACE
        //
        if (digitalRead(KEYBOARD_INT) == LOW)
        {
            Wire.requestFrom(KEYBOARD_I2C_ADDR, 1); // request 1 byte from keyboard
            while (Wire.available())
            {
                uint8_t key_val = Wire.read(); // receive a byte as character
                String msg((char)key_val);

                switch ((char)key_val)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (strobe_fonction < 2)
                    {
                        strobe_red = PRESET_MEM_COLOR_STR[key_val - 48][0];
                        strobe_green = PRESET_MEM_COLOR_STR[key_val - 48][1];
                        strobe_blue = PRESET_MEM_COLOR_STR[key_val - 48][2];

                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_MEM);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, (page_mem + msg).c_str(), 1);
                        msg += " " + strobe_mqtt_topic + (page_mem + msg);

                        send_master_str();
                    }
                    else if (strobe_fonction == 2)
                    {
                        strobe_red = PRESET_COLOR_STR[key_val - 48][0];
                        strobe_green = PRESET_COLOR_STR[key_val - 48][1];
                        strobe_blue = PRESET_COLOR_STR[key_val - 48][2];

                        msg += " " + NAME_PRESET_COLOR_STR[key_val - 48];
                        msg += "|" + strobe_mqtt_topic + "|";
                        msg += "R " + String(strobe_red) + " G " + String(strobe_green);
                        msg += " B " + String(strobe_blue);

                        send_color_str();
                    }
                    else if (strobe_fonction == 3)
                    {
                        strobe_red = PRESET_RED[key_val - 48];

                        msg += " " + NAME_PRESET_RED[key_val - 48];

                        send_red_str();
                    }
                    else if (strobe_fonction == 4)
                    {
                        strobe_green = PRESET_GREEN[key_val - 48];

                        msg += " " + NAME_PRESET_GREEN[key_val - 48];

                        send_green_str();
                    }
                    else if (strobe_fonction == 5)
                    {
                        strobe_blue = PRESET_BLUE[key_val - 48];

                        msg += " " + NAME_PRESET_BLUE[key_val - 48];

                        send_blue_str();
                    }
                    break;

                case '.':
                    strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_STOP);
                    strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                    ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                    msg += " " + strobe_mqtt_topic;
                    break;
                case '=':
                    if (strobe_fonction < 2)
                    {
                        master_value_str();
                        msg = "Master " + strobe_Mast + " SEND";
                    }
                    else if (strobe_fonction == 2)
                    {
                        color_value_str();
                        send_color_str();
                        msg = "Color SEND";
                        msg += "|" + light_mqtt_topic + "|";
                        msg += "R " + String(strobe_red) + " G " + String(strobe_green);
                        msg += " B " + String(strobe_blue);
                    }
                    else if (strobe_fonction == 3)
                    {
                        rgb_value_str(0);
                        msg = "SEND ";
                        msg += "|" + strobe_mqtt_topic + "|";
                        msg += "Red " + String(strobe_red);
                    }
                    else if (strobe_fonction == 4)
                    {
                        rgb_value_str(1);
                        msg = "SEND ";
                        msg += "|" + strobe_mqtt_topic + "|";
                        msg += "Green " + String(strobe_green);
                    }
                    else if (strobe_fonction == 5)
                    {
                        rgb_value_str(2);
                        msg = "SEND ";
                        msg += "|" + strobe_mqtt_topic + "|";
                        msg += "Blue " + String(strobe_blue);
                    }
                    break;
                case '-':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_Master -= 2;
                        if (strobe_Master < 0)
                        {
                            strobe_Master = 0;
                        }
                        send_master_str();
                        msg += "|" + strobe_mqtt_topic + "|" + strobe_Mast.c_str();
                    }
                    else if (strobe_fonction == 1)
                    {
                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_SLOWER);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                        msg += " " + strobe_mqtt_topic;
                    }
                    else if (strobe_fonction == 3)
                    {
                        strobe_red -= 1;
                        if (strobe_red < 0)
                        {
                            strobe_red = 0;
                        }
                        send_red_str();
                    }
                    else if (strobe_fonction == 4)
                    {
                        strobe_green -= 1;
                        if (strobe_green < 0)
                        {
                            strobe_green = 0;
                        }
                        send_green_str();
                    }
                    else if (strobe_fonction == 5)
                    {
                        strobe_blue -= 1;
                        if (strobe_blue < 0)
                        {
                            strobe_blue = 0;
                        }
                        send_blue_str();
                    }
                    break;
                case '+':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_Master += 2;
                        if (strobe_Master > 255)
                        {
                            strobe_Master = 255;
                        }
                        send_master_str();
                        msg += "|" + strobe_mqtt_topic + "|" + strobe_Mast.c_str();
                    }
                    else if (strobe_fonction == 1)
                    {
                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FASTER);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                        msg += " " + strobe_mqtt_topic;
                    }
                    else if (strobe_fonction == 3)
                    {
                        strobe_red += 1;
                        if (strobe_red > 255)
                        {
                            strobe_red = 255;
                        }
                        send_red_str();
                    }
                    else if (strobe_fonction == 4)
                    {
                        strobe_green += 1;
                        if (strobe_green > 255)
                        {
                            strobe_green = 255;
                        }
                        send_green_str();
                    }
                    else if (strobe_fonction == 5)
                    {
                        strobe_blue += 1;
                        if (strobe_blue > 255)
                        {
                            strobe_blue = 255;
                        }
                        send_blue_str();
                    }
                    break;

                case 'A':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_Master = 255;
                        send_master_str();
                        msg += "|" + strobe_mqtt_topic + "|" + strobe_Mast.c_str();
                    }
                    else if (strobe_fonction == 3)
                    {
                        strobe_red = 255;
                        msg += "Full Red value";
                        send_red_str();
                    }
                    else if (strobe_fonction == 4)
                    {
                        strobe_green = 255;
                        msg += "Full Green value";
                        send_green_str();
                    }
                    else if (strobe_fonction == 5)
                    {
                        strobe_blue = 255;
                        msg += "Full Blue value";
                        send_blue_str();
                    }
                    break;
                case 'M':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FADE_IN);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                        msg += " " + strobe_mqtt_topic;
                    }
                    else if (strobe_fonction == 1)
                    {
                    }
                    break;
                case '%':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_FADE_OUT);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                        msg += " " + strobe_mqtt_topic;
                    }
                    else if (strobe_fonction == 1)
                    {
                    }
                    break;
                case '/':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_Master -= 10;
                        if (strobe_Master < 0)
                        {
                            strobe_Master = 0;
                        }
                        send_master_str();
                        msg += "|" + strobe_mqtt_topic + "|" + strobe_Mast.c_str();
                    }
                    else if (strobe_fonction == 1)
                    {
                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_SMALLER);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                        msg += " " + strobe_mqtt_topic;
                    }
                    else if (strobe_fonction == 2)
                    {
                    }
                    else if (strobe_fonction == 3)
                    {
                        strobe_red -= 10;
                        if (strobe_red < 0)
                        {
                            strobe_red = 0;
                        }
                        send_red_str();
                    }
                    else if (strobe_fonction == 4)
                    {
                        strobe_green -= 10;
                        if (strobe_green < 0)
                        {
                            strobe_green = 0;
                        }
                        send_green_str();
                    }
                    else if (strobe_fonction == 5)
                    {
                        strobe_blue -= 10;
                        if (strobe_blue < 0)
                        {
                            strobe_blue = 0;
                        }
                        send_blue_str();
                    }
                    break;
                case '*':
                    if (strobe_fonction == 0 || strobe_fonction == 2)
                    {
                        strobe_Master += 10;
                        if (strobe_Master > 255)
                        {
                            strobe_Master = 255;
                        }
                        send_master_str();
                        msg += "|" + strobe_mqtt_topic + "|" + strobe_Mast.c_str();
                    }
                    else if (strobe_fonction == 1)
                    {
                        strobe_mqtt_topic = String(STROBE_MQTT_K32) + String(STROBE_MQTT_ID) + String(STROBE_MQTT_BIGGER);
                        strobe_mqtt_topic.toCharArray(strobe_mqtt_topic_c, strobe_mqtt_topic.length() + 1);
                        ez.mqtt32->publish(strobe_mqtt_topic_c, nullptr, 1);
                        msg += " " + strobe_mqtt_topic;
                    }
                    else if (strobe_fonction == 2)
                    {
                    }
                    else if (strobe_fonction == 3)
                    {
                        strobe_red += 10;
                        if (strobe_red > 255)
                        {
                            strobe_red = 255;
                        }
                        send_red_str();
                    }
                    else if (strobe_fonction == 4)
                    {
                        strobe_green += 10;
                        if (strobe_green > 255)
                        {
                            strobe_green = 255;
                        }
                        send_green_str();
                    }
                    else if (strobe_fonction == 5)
                    {
                        strobe_blue += 10;
                        if (strobe_blue > 255)
                        {
                            strobe_blue = 255;
                        }
                        send_blue_str();
                    }
                    break;
                case '`':
                    if (strobe_fonction == 2)
                    {
                        color_front_back_str = !color_front_back_str;
                        if (color_front_back_str)
                        {
                            msg += "| COLOR BACK";
                        }
                        else
                        {
                            msg += "| COLOR FRONT";
                        }
                    }
                    else if (strobe_fonction == 4)
                    {
                        _mod_coarse_str = !_mod_coarse_str;
                        if (_mod_coarse_str)
                        {
                            msg += "| Fine +- 1";
                            inc_value = 2;
                        }
                        else
                        {
                            msg += "| Coarse +- 10";
                            inc_value = 10;
                        }
                    }

                    break;
                }
                LOG(msg);
                ez.msgBox("M5 REMOTE STROBE", msg, "id|" + id_cal_strobe + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
                draw_master_str();
            }
        }
    }
}

#endif