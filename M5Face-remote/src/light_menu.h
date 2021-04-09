#include "preset_light.h"

void remote_light();

void master_value();
void id_value();
void color_value();
void draw_master();
void send_master();
void send_color();
void draw_coloe();
void send_str();
void draw_str();
void send_mod();
void draw_mod();
void send_mirror();
void draw_mirror();

bool _mod_coarse = false;
bool color_front_back = false;
uint8_t light_fonction = 0;

String MQTT_ID = "all";
String MQTT_K32 = "k32/";

String light_id_calling = "";

uint8_t light_id_fonction = 0;
String light_id_fonct = "ID";

uint8_t red, green, blue, white, str, mod, mirror;
int16_t str_speed = 127;
int16_t pix_long = 127;
int16_t pix_pos = 127;
int16_t zoom = 255;

String light_mqtt_frame;

int16_t Master = 255;
String _Mast = String(Master);

char LIGHT_MQTT_TOPIC[] = "k32/all/leds/master/tenless";
String light_mqtt_topic;
String LIGHT_MQTT_MEM = "/leds/mem";
String LIGHT_MQTT_STOP = "/leds/stop";
String LIGHT_MQTT_SLOWER = "/leds/modall/slower";
String LIGHT_MQTT_SMALLER = "/leds/modall/smaller";
String LIGHT_MQTT_FASTER = "/leds/modall/faster";
String LIGHT_MQTT_BIGGER = "/leds/modall/bigger";
String LIGHT_MQTT_FADE_IN = "/leds/master/fadein";
String LIGHT_MQTT_FADE_OUT = "/leds/master/fadeout";
String LIGHT_MQTT_MASTER = "/leds/master";
String LIGHT_MQTT_FRAME = "/leds/frame";

// String LIGHT_MQTT_COLOR_ALL = "/leds/all";
// String LIGHT_MQTT_COLOR_STRIP = "/leds/strip";
// String LIGHT_MQTT_COLOR_PIXEL = "/leds/pixel";
// String LIGHT_MQTT_LESS = "/leds/master/less";
// String LIGHT_MQTT_TENLESS = "/leds/master/tenless";
// String LIGHT_MQTT_MORE = "/leds/master/more";
// String LIGHT_MQTT_TENMORE = "/leds/master/tenmore";
// String LIGHT_MQTT_FULL = "/leds/master/full";

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW MIRROR/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_mirror()
{

    m5.lcd.setTextColor(TFT_ORANGE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Zoom : " + String(zoom), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND MIRROR/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_mirror()
{
    light_mqtt_frame = "-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|";

    light_mqtt_frame += String(mirror) + "|" + String(zoom);
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FRAME);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    k32->mqtt->publish(LIGHT_MQTT_TOPIC, light_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW MOD////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_mod()
{

    m5.lcd.setTextColor(TFT_ORANGE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Longeur : " + String(pix_long), TFT_W - ez.theme->input_hmargin, text_h);
    m5.lcd.setTextColor(TFT_PURPLE);
    m5.lcd.drawString("Position : " + String(pix_pos), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
    m5.lcd.setTextColor(TFT_GREEN);
    if (_mod_coarse)
    {
        m5.lcd.drawString("Fine", TFT_W - ez.theme->input_hmargin, 150 + ez.theme->input_vmargin + text_h + 10);
    }
    else
    {
        m5.lcd.drawString("Coarse", TFT_W - ez.theme->input_hmargin, 150 + ez.theme->input_vmargin + text_h + 10);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND MOD////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_mod()
{
    light_mqtt_frame = "-1|-1|-1|-1|-1|";

    light_mqtt_frame += String(mod) + "|" + String(pix_long) + "|" + String(pix_pos);
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FRAME);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    k32->mqtt->publish(LIGHT_MQTT_TOPIC, light_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW STR////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_str()
{

    m5.lcd.setTextColor(TFT_RED);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();

    m5.lcd.drawString("Str speed: " + String(str_speed), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND STR////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_str()
{
    light_mqtt_frame = "-1|-1|-1|-1|-1|-1|-1|-1|";

    light_mqtt_frame += String(str) + "|" + String(str_speed);
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FRAME);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    k32->mqtt->publish(LIGHT_MQTT_TOPIC, light_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW COLOR//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_color()
{

    m5.lcd.setTextColor(TFT_RED);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    if (color_front_back)
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
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_color()
{
    if (color_front_back)
    {
        light_mqtt_frame = "-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|";
    }
    else
    {
        light_mqtt_frame = "-1|";
    }
    light_mqtt_frame += String(red) + "|" + String(green) + "|" + String(blue) + "|" + String(white);
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FRAME);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    k32->mqtt->publish(LIGHT_MQTT_TOPIC, light_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND MASTER/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void send_master()
{
    _Mast = String(Master);
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MASTER);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    k32->mqtt->publish(LIGHT_MQTT_TOPIC, _Mast.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW MASTER/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_master()
{
    m5.lcd.setTextColor(TFT_WHITE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Master:" + String(Master), 10, 10 + ez.theme->input_vmargin + text_h + 10);
    if (light_fonction == 2)
    {
        draw_color();
    }
    else if (light_fonction == 3)
    {
        draw_str();
    }
    else if (light_fonction == 4)
    {
        draw_mod();
    }
    else if (light_fonction == 5)
    {
        draw_mirror();
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////COLOR_VALUE//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void color_value()
{
    bool r, g, b, w = false;
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";
    uint8_t color_fonction = 0;
    String color_fonct = "RED";
    int res;

    msg += " Enter RED value & =";
    ez.msgBox("M5 REMOTE LIGHT", msg, "##" + color_fonct + "###Back", false);
    draw_master();

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            main_origine = false;
            remote_light();
        };
        if (M5.BtnB.wasPressed())
        {
            color_fonction += 1;
            if (color_fonction >= 4)
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
            else if (color_fonction == 3)
            {
                color_fonct = "WHITE";
                msg = "";
                msg += " Enter WHITE value & =";
            }

            ez.msgBox("M5 REMOTE LIGHT", msg, "##" + color_fonct + "###Back", false);
            draw_master();
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
                    if (bad == true)
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
                            red = res_value.toInt();
                            r = true;
                        }
                        else if (color_fonction == 1)
                        {
                            green = res_value.toInt();
                            g = true;
                        }
                        else if (color_fonction == 2)
                        {
                            blue = res_value.toInt();
                            b = true;
                        }
                        else if (color_fonction == 3)
                        {
                            white = res_value.toInt();
                            w = true;
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
                        else if (color_fonction == 3)
                        {
                            w = true;
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
                        else if (color_fonction == 3)
                        {
                            color_fonct = "WHITE";
                            msg += " Enter WHITE value & =";
                            w = false;
                        }
                        ez.msgBox("M5 REMOTE LIGHT", msg, "##" + color_fonct + "###Back", false);
                        draw_master();
                    }
                    if (r == true && g == true && b == true && w == true)
                    {
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        if (color_fonction >= 4)
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
                        else if (color_fonction == 3)
                        {
                            color_fonct = "WHITE";
                            msg = "";
                            msg += " Enter WHITE value & =";
                        }
                        ez.msgBox("M5 REMOTE LIGHT", msg, "##" + color_fonct + "###Back", false);
                        draw_master();
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
                    else if (color_fonction == 3)
                    {
                        color_fonct = "WHITE";
                        msg = "";
                        msg += " Enter WHITE value & =";
                    }

                    ez.msgBox("M5 REMOTE LIGHT", msg, "##" + color_fonct + "###Back", false);
                    draw_master();
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                    ez.msgBox("M5 REMOTE LIGHT", res_value, "##" + color_fonct + "###Back", false);
                draw_master();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////ID_VALUE//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void id_value()
{
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";

    msg += " Enter N° ID & =";
    ez.msgBox("M5 REMOTE LIGHT", msg, "##" + light_id_fonct + "###Back", false);
    draw_master();

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            main_origine = false;
            remote_light();
        };

        if (M5.BtnB.wasPressed())
        {
            light_id_fonction += 1;
            if (light_id_fonction >= 2)
            {
                light_id_fonction = 0;
            }
            if (light_id_fonction == 0)
            {
                light_id_fonct = "ID";
                msg = "";
                msg += " Enter N° ID & =";
            }
            else if (light_id_fonction == 1)
            {
                light_id_fonct = "CH";
                msg = "";
                msg += " Enter N° CH & =";
            }

            ez.msgBox("M5 REMOTE LIGHT", msg, "##" + light_id_fonct + "###Back", false);
            draw_master();
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
                    if (bad == true)
                        bad = false;
                    res_value += value;
                    break;

                case '.':
                    break;
                case '=':
                    if (light_id_fonction == 0)
                    {
                        MQTT_ID = String('e') + String(res_value);
                    }
                    else if (light_id_fonction == 1)
                    {
                        MQTT_ID = String('c') + String(res_value);
                    }
                    light_id_calling = String(res_value);
                    equal = true;
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    res_value = "";
                    if (light_id_fonction == 0)
                    {
                        light_id_fonct = "ID";
                        msg = "";
                        msg += " Enter N° ID & =";
                    }
                    else if (light_id_fonction == 1)
                    {
                        light_id_fonct = "CH";
                        msg = "";
                        msg += " Enter N° CH & =";
                    }

                    ez.msgBox("M5 REMOTE LIGHT", msg, "##" + light_id_fonct + "###Back", false);
                    draw_master();
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                    ez.msgBox("M5 REMOTE LIGHT", res_value, "##" + light_id_fonct + "###Back", false);
                draw_master();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////MASTER_VALUE/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void master_value()
{
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";
    int res;

    msg += " Enter value to master 0 -> 255 & =";
    ez.msgBox("M5 REMOTE LIGHT", msg, "#####Back", false);
    draw_master();

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            main_origine = false;
            remote_light();
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
                    if (bad == true)
                        bad = false;
                    res_value += value;
                    break;

                case '.':
                    break;
                case '=':

                    if (res < 256)
                    {
                        Master = res_value.toInt();
                        send_master();
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to master 0 -> 255 & =";
                        ez.msgBox("M5 REMOTE LIGHT", msg, "#####Back", false);
                        draw_master();
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
                    ez.msgBox("M5 REMOTE LIGHT", msg, "#####Back", false);
                    draw_master();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE LIGHT", res_value, "#####Back", false);
                draw_master();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////REMOTE_LULU//////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void remote_light()
{
    uint32_t _widget_time = millis();
    uint8_t inc_value = 10;
    bool _a_b = true;
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MEM);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    uint8_t id_call = 0;
    String id_cal = "all";
    String fonct = "Master";
    uint8_t page_mem = 0;
    String page_me = "0-9";
    ez.msgBox("M5 REMOTE LIGHT", "Welcome", id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
    draw_master();

    while (true)
    {
        M5.update();
        ez.yield();
        // if (millis() > _widget_time + ez.theme->signal_interval)
        // {
        //     ez.header.draw("battery");
        //     ez.header.draw("wifi");
        //     ez.mqtt.mqtt_on = k32->mqtt->isConnected();
        //     ez.mqtt.mqtt();
        //     _widget_time = millis();
        // }

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (m5.BtnA.pressedFor(ez.theme->longpress_time))
        {
            if (_a_b)
            {
                ez.msgBox("M5 REMOTE LIGHT", "Release for Back Menu", id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
                _a_b = false;
            }
        };
        if (m5.BtnA.wasReleasefor(ez.theme->longpress_time))
        {
            if (main_origine)
            {
                break;
            }
            else
            {
                main_menu();
            }
        };

        if (m5.BtnA.wasReleased())
        {
            id_call += 1;
            if (id_call >= 2)
            {
                id_call = 0;
            }
            if (id_call == 0)
            {
                id_cal = "all";
                MQTT_ID = "all";
                ez.msgBox("M5 REMOTE LIGHT", id_cal, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
                draw_master();
            }
            else if (id_call == 1)
            {
                id_value();
                if (light_id_fonction == 0)
                {
                    id_cal = "id" + light_id_calling;
                }
                else if (light_id_fonction == 1)
                {
                    id_cal = "ch" + light_id_calling;
                }
                ez.msgBox("M5 REMOTE LIGHT", id_cal, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
                draw_master();
            }
            light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MEM);
            light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
        };

        if (M5.BtnB.wasPressed())
        {
            light_fonction += 1;
            if (light_fonction >= 6)
            {
                light_fonction = 0;
            }
            if (light_fonction == 0)
            {
                fonct = "Master";
            }
            else if (light_fonction == 1)
            {
                fonct = "Speed";
            }
            else if (light_fonction == 2)
            {
                fonct = "Color";
            }
            else if (light_fonction == 3)
            {
                fonct = "Strobe";
            }
            else if (light_fonction == 4)
            {
                fonct = "Pixel Mode";
            }
            else if (light_fonction == 5)
            {
                fonct = "Mirror";
            }

            ez.msgBox("M5 REMOTE LIGHT", fonct, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
            draw_master();
        };

        if (M5.BtnC.wasPressed())
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
            ez.msgBox("M5 REMOTE LIGHT", page_me, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
            draw_master();
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
                    if (light_fonction < 2)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MEM);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, (page_mem + msg).c_str(), 1);
                        msg += " " + light_mqtt_topic + (page_mem + msg);

                        send_master();
                    }
                    else if (light_fonction == 2)
                    {
                        red = PRESET_COLOR[key_val - 48][0];
                        green = PRESET_COLOR[key_val - 48][1];
                        blue = PRESET_COLOR[key_val - 48][2];
                        white = PRESET_COLOR[key_val - 48][3];

                        msg += " " + NAME_PRESET_COLOR[key_val - 48];

                        send_color();
                        msg += "|" + light_mqtt_topic + "|";
                        msg += "R " + String(red) + " G " + String(green);
                        msg += " B " + String(blue) + " W " + String(white);

                        send_master();
                    }
                    else if (light_fonction == 3)
                    {
                        str = PRESET_STR[key_val - 48];

                        msg += " " + NAME_PRESET_STR[key_val - 48];

                        send_str();
                    }
                    else if (light_fonction == 4)
                    {
                        mod = PRESET_MOD[key_val - 48];

                        msg += " " + NAME_PRESET_MOD[key_val - 48];

                        send_mod();
                    }
                    else if (light_fonction == 5)
                    {
                        mod = PRESET_MIRROR[key_val - 48];

                        msg += " " + NAME_PRESET_MIRROR[key_val - 48];

                        send_mirror();
                    }
                    break;

                case '.':
                    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_STOP);
                    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                    k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                    msg += " " + light_mqtt_topic;
                    break;
                case '=':
                    if (light_fonction == 0 || light_fonction == 3 || light_fonction == 5)
                    {
                        master_value();
                        msg = "Master " + _Mast + " SEND";
                    }
                    else if (light_fonction == 1)
                    {
                    }
                    else if (light_fonction == 2 || light_fonction == 4)
                    {
                        color_value();
                        send_color();
                        msg = "Color SEND";
                        msg += "|" + light_mqtt_topic + "|";
                        msg += "R " + String(red) + " G " + String(green);
                        msg += " B " + String(blue) + " W " + String(white);
                    }
                    break;
                case '-':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        Master -= 2;
                        if (Master < 0)
                        {
                            Master = 0;
                        }
                        send_master();
                        msg += "|" + light_mqtt_topic + "|" + _Mast.c_str();
                    }
                    else if (light_fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_SLOWER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (light_fonction == 3)
                    {
                        str_speed -= 2;
                        if (str_speed < 0)
                        {
                            str_speed = 0;
                        }
                        send_str();
                    }
                    else if (light_fonction == 4)
                    {
                        pix_pos -= inc_value;
                        if (pix_pos < 0)
                        {
                            pix_pos = 0;
                        }
                        send_mod();
                    }
                    else if (light_fonction == 5)
                    {
                        zoom -= 2;
                        if (zoom < 0)
                        {
                            zoom = 0;
                        }
                        send_mirror();
                    }
                    break;
                case '+':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        Master += 2;
                        if (Master > 255)
                        {
                            Master = 255;
                        }
                        send_master();
                        msg += "|" + light_mqtt_topic + "|" + _Mast.c_str();
                    }
                    else if (light_fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FASTER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (light_fonction == 3)
                    {
                        str_speed += 2;
                        if (str_speed > 255)
                        {
                            str_speed = 255;
                        }
                        send_str();
                    }
                    else if (light_fonction == 4)
                    {
                        pix_pos += inc_value;
                        if (pix_pos > 255)
                        {
                            pix_pos = 255;
                        }
                        send_mod();
                    }
                    else if (light_fonction == 5)
                    {
                        zoom += 2;
                        if (zoom > 255)
                        {
                            zoom = 255;
                        }
                        send_mirror();
                    }
                    break;

                case 'A':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        Master = 255;
                        send_master();
                        msg += "|" + light_mqtt_topic + "|" + _Mast.c_str();
                    }
                    else if (light_fonction == 4)
                    {
                        pix_pos = 127;
                        pix_long = 127;
                        msg += "Reset Pixel value";
                        send_mod();
                    }

                    else if (light_fonction == 5)
                    {
                        zoom = 255;
                        msg += "Reset Zoom value";
                        send_mirror();
                    }
                    break;
                case 'M':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FADE_IN);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (light_fonction == 1)
                    {
                    }
                    break;
                case '%':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FADE_OUT);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (light_fonction == 1)
                    {
                    }
                    break;
                case '/':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        Master -= 10;
                        if (Master < 0)
                        {
                            Master = 0;
                        }
                        send_master();
                        msg += "|" + light_mqtt_topic + "|" + _Mast.c_str();
                    }
                    else if (light_fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_SMALLER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (light_fonction == 2)
                    {
                    }
                    else if (light_fonction == 3)
                    {
                        str_speed -= 10;
                        if (str_speed < 0)
                        {
                            str_speed = 0;
                        }
                        send_str();
                    }
                    else if (light_fonction == 4)
                    {
                        pix_long -= inc_value;
                        if (pix_long < 0)
                        {
                            pix_long = 0;
                        }
                        send_mod();
                    }
                    else if (light_fonction == 5)
                    {
                        zoom -= 10;
                        if (zoom < 0)
                        {
                            zoom = 0;
                        }
                        send_mirror();
                    }
                    break;
                case '*':
                    if (light_fonction == 0 || light_fonction == 2)
                    {
                        Master += 10;
                        if (Master > 255)
                        {
                            Master = 255;
                        }
                        send_master();
                        msg += "|" + light_mqtt_topic + "|" + _Mast.c_str();
                    }
                    else if (light_fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_BIGGER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (light_fonction == 2)
                    {
                    }
                    else if (light_fonction == 3)
                    {
                        str_speed += 10;
                        if (str_speed > 255)
                        {
                            str_speed = 255;
                        }
                        send_str();
                    }
                    else if (light_fonction == 4)
                    {
                        pix_long += inc_value;
                        if (pix_long > 255)
                        {
                            pix_long = 255;
                        }
                        send_mod();
                    }
                    else if (light_fonction == 5)
                    {
                        zoom += 10;
                        if (zoom > 255)
                        {
                            zoom = 255;
                        }
                        send_mirror();
                    }
                    break;
                case '`':
                    if (light_fonction == 2)
                    {
                        color_front_back = !color_front_back;
                        if (color_front_back)
                        {
                            msg += "| COLOR BACK";
                        }
                        else
                        {
                            msg += "| COLOR FRONT";
                        }
                    }
                    else if (light_fonction == 4)
                    {
                        _mod_coarse = !_mod_coarse;
                        if (_mod_coarse)
                        {
                            msg += "| Fine +- 2";
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
                ez.msgBox("M5 REMOTE LIGHT", msg, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
                draw_master();
            }
        }
    }
}
