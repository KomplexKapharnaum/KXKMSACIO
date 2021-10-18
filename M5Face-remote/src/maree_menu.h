#ifndef MAREE_MENU_H
#define MAREE_MENU_H

// #include "preset_maree.h"

void remote_maree();

bool pixel_value();
bool maree_id_value();
bool haute_value();
bool basse_value();
bool temps_value();

void draw_pixel();
void draw_haute();
void draw_basse();
void draw_temps();

void send_pixel();
void send_haute();
void send_basse();
void send_temps();
void send_go_up();
void send_go_down();

// bool _mod_coarse = false;
// bool color_front_back = false;
uint8_t maree_fonction = 0;
bool esc_maree = true;

String MAREE_MQTT_ID = "all";
String MAREE_MQTT_K32 = "k32/";

uint8_t maree_id_fonction = 1;
String maree_id_fonct = "CH";
String id_cal_maree = "all";

uint16_t Pixel, haute, basse, temps;

String _Pixel = String(Pixel);
String _haute = String(haute);
String _basse = String(basse);
String _temps = String(temps);

char MAREE_MQTT_TOPIC[] = "k32/all/leds/maree/tenless";
String maree_mqtt_topic;
String MAREE_MQTT_Pixel = "/leds/maree/pixel";
String MAREE_MQTT_HAUTE = "/leds/maree/haute";
String MAREE_MQTT_BASSE = "/leds/maree/basse";
String MAREE_MQTT_TEMPS = "/leds/maree/temps";
String MAREE_MQTT_GO_UP = "/leds/maree/go_p";
String MAREE_MQTT_GO_DOWN = "/leds/maree/go_m";

String MAREE_MQTT_MASTER = "/leds/master";
String MAREE_MQTT_STOP = "/leds/stop";
String MAREE_MQTT_MEM = "/leds/mem";
String MAREE_MQTT_FADE_IN = "/leds/master/fadein";
String MAREE_MQTT_FADE_OUT = "/leds/master/fadeout";
String maree_mqtt_frame = "";

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw()
{
    draw_pixel();
    draw_haute();
    draw_basse();
    draw_temps();
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW PIXEL//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_pixel()
{

    m5.lcd.setTextColor(TFT_RED);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Pixel:" + String(Pixel), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW HAUTE//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_haute()
{
    m5.lcd.setTextColor(TFT_BLUE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("haute:" + String(haute), 10, 10 + ez.theme->input_vmargin + text_h + 10);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW BASSE//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_basse()
{
    m5.lcd.setTextColor(TFT_CYAN);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("basse:" + String(basse), 10, 10 + ez.theme->input_vmargin + text_h + 35);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW TEMPS//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_temps()
{
    m5.lcd.setTextColor(TFT_ORANGE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("temps:" + String(temps), TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 35);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND HAUTE//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_haute()
{
    _haute = String(haute);
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_HAUTE);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    k32->mqtt->publish(MAREE_MQTT_TOPIC, _haute.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND BASSE//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_basse()
{
    _basse = String(basse);
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_BASSE);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    k32->mqtt->publish(MAREE_MQTT_TOPIC, _basse.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND Pixel/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void send_pixel()
{
    _Pixel = String(Pixel);
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_Pixel);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    k32->mqtt->publish(MAREE_MQTT_TOPIC, _Pixel.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND TEMPS//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_temps()
{
    _temps = String(temps);
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_TEMPS);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    k32->mqtt->publish(MAREE_MQTT_TOPIC, _temps.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND GO_UP//////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_go_up()
{
    maree_mqtt_frame = "";
    maree_mqtt_frame += String(temps) + "|" + String(haute)+ "|" + String(basse);
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_GO_UP);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    k32->mqtt->publish(MAREE_MQTT_TOPIC, maree_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////SEND GO_DOWN////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
//{master , r  , g  , b  , w  ,pix mod , pix long , pix_pos , str_mod , str_speed , r_fond , g_fond , b_fond , w_fond , mirror_mod , zoom }
void send_go_down()
{
    maree_mqtt_frame = "";
    maree_mqtt_frame += String(temps) + "|" + String(haute)+ "|" + String(basse);
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_GO_DOWN);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    k32->mqtt->publish(MAREE_MQTT_TOPIC, maree_mqtt_frame.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////HAUTE_VALUE//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool haute_value()
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;
    esc_maree = true;

    msg += " Enter haute to pixel 0 -> 300 & =";
    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
    draw();

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

                    if (res < 301)
                    {
                        haute = res_value.toInt();
                        send_haute();
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter haute to pixel 0 -> 300 & =";
                        ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                        draw();
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
                    msg += " Enter haute to pixel 0 -> 300 & =";
                    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                    draw();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE MAREE", res_value, "#####Back", false);
                draw();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////BASSE_VALUE//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool basse_value()
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;
    esc_maree = true;

    msg += " Enter basse to pixel 0 -> 300 & =";
    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
    draw();

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

                    if (res < 300)
                    {
                        basse = res_value.toInt();
                        send_basse();
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter basse to pixel 0 -> 300 & =";
                        ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                        draw();
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
                    msg += " Enter basse to pixel 0 -> 300 & =";
                    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                    draw();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE MAREE", res_value, "#####Back", false);
                draw();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////TEMPS_VALUE//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool temps_value()
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;
    esc_maree = true;

    msg += " Enter temps en Secondes & =";
    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
    draw();

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

                    if (res < 32768)
                    {
                        temps = res_value.toInt();
                        send_temps();
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter temps en Secondes & =";
                        ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                        draw();
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
                    msg += " Enter temps en Secondes & =";
                    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                    draw();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE MAREE", res_value, "#####Back", false);
                draw();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////MAREE_ID_VALUE////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

bool maree_id_value()
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";

    msg += " Enter N° CH & =";
    msg += "|0 = all";

    ez.msgBox("M5 REMOTE MAREE", msg, "## idmode|" + maree_id_fonct + "### Back", false);
    draw();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        // BTN A/B/C
        if (action == "Back")
            return false;

        if (action == "idmode")
        {
            maree_id_fonction += 1;
            if (maree_id_fonction >= 2)
            {
                maree_id_fonction = 0;
            }
            if (maree_id_fonction == 0)
            {
                maree_id_fonct = "ID";
                msg = "";
                msg += " Enter N° ID & =";
                msg += "|0 = all";
                ez.msgBox("M5 REMOTE MAREE", msg, "## idmode|" + maree_id_fonct + "### Back", false);
                draw;
            }
            else if (maree_id_fonction == 1)
            {
                maree_id_fonct = "CH";
                msg = "";
                msg += " Enter N° CH & =";
                msg += "|0 = all";
                ez.msgBox("M5 REMOTE MAREE", msg, "## idmode|" + maree_id_fonct + "### Back", false);
                draw;
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
                        MAREE_MQTT_ID = "all";
                        id_cal_maree = "all";
                    }
                    else if (maree_id_fonction == 0)
                    {
                        MAREE_MQTT_ID = String('e') + String(res_value);
                        id_cal_maree = "id" + res_value;
                    }
                    else if (maree_id_fonction == 1)
                    {
                        MAREE_MQTT_ID = String('c') + String(res_value);
                        id_cal_maree = "ch" + res_value;
                    }
                    return true;
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    res_value = "";
                    if (maree_id_fonction == 0)
                    {
                        maree_id_fonct = "ID";
                        msg = "";
                        msg += " Enter N° ID & =";
                        msg += "|0 = all";
                    }
                    else if (maree_id_fonction == 1)
                    {
                        maree_id_fonct = "CH";
                        msg = "";
                        msg += " Enter N° CH & =";
                        msg += "|0 = all";
                    }

                    ez.msgBox("M5 REMOTE MAREE", msg, "## idmode|" + maree_id_fonct + "### Back", false);
                    draw;
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE MAREE", res_value, "## idmode|" + maree_id_fonct + "### Back", false);
                    draw;
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////pixel_value/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool pixel_value()
{
    bool bad = false;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;
    esc_maree = true;

    msg += " Enter value to Pixel 0 -> 300 & =";
    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
    draw();

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

                    if (res < 301)
                    {
                        Pixel = res_value.toInt();
                        send_pixel();
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to Pixel 0 -> 300 & =";
                        ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                        draw();
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
                    msg += " Enter value to Pixel 0 -> 300 & =";
                    ez.msgBox("M5 REMOTE MAREE", msg, "#####Back", false);
                    draw();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE MAREE", res_value, "#####Back", false);
                draw();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////REMOTE_MAREE/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void remote_maree()
{
    uint32_t _widget_time = millis();
    uint8_t inc_value = 10;
    String action = "";
    bool _a_b = true;
    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_MEM);
    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
    String fonct = "Pixel";
    uint8_t page_mem = 0;
    String page_me = "0-9";

    ez.msgBox("M5 REMOTE MAREE", "Welcome", "id|" + id_cal_maree + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
    draw();

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
            maree_id_value();

            ez.msgBox("M5 REMOTE MAREE", id_cal_maree, "id|" + id_cal_maree + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
            draw();
        };

        if (action == "func")
        {
            maree_fonction += 1;
            if (maree_fonction >= 6)
            {
                maree_fonction = 0;
            }
            if (maree_fonction == 0)
            {
                fonct = "Pixel";
            }
            else if (maree_fonction == 1)
            {
                fonct = "Speed";
            }
            else if (maree_fonction == 2)
            {
                fonct = "Color";
            }
            else if (maree_fonction == 3)
            {
                fonct = "Strobe";
            }
            else if (maree_fonction == 4)
            {
                fonct = "Pixel Mode";
            }
            else if (maree_fonction == 5)
            {
                fonct = "Mirror";
            }

            ez.msgBox("M5 REMOTE MAREE", fonct, "id|" + id_cal_maree + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
            draw();
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

            ez.msgBox("M5 REMOTE MAREE", page_me, "id|" + id_cal_maree + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
            draw();
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
                    maree_mqtt_topic = String(MAREE_MQTT_K32) + String(MAREE_MQTT_ID) + String(MAREE_MQTT_MEM);
                    maree_mqtt_topic.toCharArray(MAREE_MQTT_TOPIC, maree_mqtt_topic.length() + 1);
                    k32->mqtt->publish(MAREE_MQTT_TOPIC, (page_mem + msg).c_str(), 1);
                    msg += " " + maree_mqtt_topic + (page_mem + msg);

                    send_pixel();

                    break;

                case '.':
                    temps_value();
                    msg = "temps " + _temps + " SEND";

                    break;
                case '=':
                    pixel_value();
                    msg = "pixel " + _Pixel + " SEND";
                    break;
                case '-':
                    Pixel -= 1;
                    if (Pixel < 0)
                    {
                        Pixel = 0;
                    }
                    send_pixel();
                    msg += "|" + maree_mqtt_topic + "|" + _Pixel.c_str();
                    break;
                case '+':
                    Pixel += 1;
                    if (Pixel > 300)
                    {
                        Pixel = 300;
                    }
                    send_pixel();
                    msg += "|" + maree_mqtt_topic + "|" + _Pixel.c_str();
                    break;

                case 'A':
                    send_go_up();
                    msg = "GO Marée haute SEND";

                    break;
                case 'M':
                    send_go_down();
                    msg = "GO Marée basse SEND";

                    break;
                case '%':
                    haute_value();
                    msg = "haute " + _haute + " SEND";
                    break;
                case '/':
                    Pixel -= 10;
                    if (Pixel < 0)
                    {
                        Pixel = 0;
                    }
                    send_pixel();
                    msg += "|" + maree_mqtt_topic + "|" + _Pixel.c_str();
                    break;
                case '*':
                    Pixel += 10;
                    if (Pixel > 300)
                    {
                        Pixel = 300;
                    }
                    send_pixel();
                    msg += "|" + maree_mqtt_topic + "|" + _Pixel.c_str();
                    break;
                case '`':
                    basse_value();
                    msg = "basse " + _basse + " SEND";
                    break;
                }
                LOG(msg);
                ez.msgBox("M5 REMOTE MAREE", msg, "id|" + id_cal_maree + "# Menu # func|" + fonct + " # # page|" + page_me + "#", false);
                draw();
            }
        }
    }
}

#endif