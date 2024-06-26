#ifndef AUDIO_MENU_H
#define AUDIO_MENU_H

void check_page_mem();
void check_fonction();
void remote_audio();
bool audio_master_value();
bool page_mem_value();
void fonction_value();
void draw_loop();
bool id_value_audio();
void draw_volume();
void send_volume();

uint8_t page_mem = 0;
String page_me = "00-09";
String id_cal = "all";
uint8_t audio_fonction = 0;
String fonct = "Bank 0";

int8_t Volume = 80;
String _Volu = String(Volume);

uint8_t audio_id_fonction = 1;
String audio_id_fonct = "CH";

bool mqtt_loop = false;

char audio_mqtt_topic_c[64];
char AUDIO_MQTT_MESSAGE[] = "000|000|000|000";
String audio_mqtt_topic;
String audio_mqtt_message;
String AUDIO_MQTT_ID = "all";
String AUDIO_MQTT_PLAY = "/play";
String AUDIO_MQTT_NOTEON = "/noteon";
String AUDIO_MQTT_NOTEOFF = "/noteoff";
String AUDIO_MQTT_STOP = "/stop";
String AUDIO_MQTT_VOLUME = "/volume";
String AUDIO_MQTT_LOOP = "/loop";
String AUDIO_MQTT_UNLOOP = "/unloop";
String AUDIO_MQTT_MIDI = "/midi";

// TODO
String AUDIO_MQTT_FADE_IN = "/volume/fadein";
String AUDIO_MQTT_FADE_OUT = "/volume/fadeout";

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////SEND_VOLUME////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void send_volume()
{
    _Volu = String(Volume);
    audio_mqtt_topic = String(MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_VOLUME);
    audio_mqtt_topic.toCharArray(audio_mqtt_topic_c, audio_mqtt_topic.length() + 1);
    ez.mqtt32->publish(audio_mqtt_topic_c, _Volu.c_str(), 1);
}

///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////ID_VALUE_AUDIO////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

bool id_value_audio()
{
    bool bad = false;
    bool _a_b = true;
    String action = "";
    String res_value = "";
    String msg = "";

    msg += " Enter N° CH & =";
    msg += "|0 = all";
    ez.msgBox("M5 REMOTE AUDIO", msg, "## func|"+audio_id_fonct + "### Back", false);
    draw_loop();
    draw_volume();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        if (action == "Back") return false;

        if (action == "func")
        {
            audio_id_fonction += 1;
            if (audio_id_fonction >= 2)
            {
                audio_id_fonction = 0;
            }
            if (audio_id_fonction == 0)
            {
                audio_id_fonct = "ID";
                msg = "";
                msg += " Enter N° ID & =";
                msg += "|0 = all";
            }
            else if (audio_id_fonction == 1)
            {
                audio_id_fonct = "CH";
                msg = "";
                msg += " Enter N° CH & =";
                msg += "|0 = all";
            }

            ez.msgBox("M5 REMOTE AUDIO", msg, "## func|"+audio_id_fonct + "###Back", false);
            draw_loop();
            draw_volume();
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
                    if (res_value == "") res_value = "0";
                    
                    if (res_value == "0")
                    {
                        AUDIO_MQTT_ID = "all";
                        id_cal = "all";
                    }
                    else if (audio_id_fonction == 0)
                    {
                        AUDIO_MQTT_ID = "e" + res_value;
                        id_cal = "id" + res_value;
                    }
                    else if (audio_id_fonction == 1)
                    {
                        AUDIO_MQTT_ID = "c" + res_value;
                        id_cal = "ch" + res_value;
                    }
                    return true;
                    break;
                case '-':

                    break;
                case '+':

                    break;

                case 'A':
                    res_value = "";
                    if (audio_id_fonction == 0)
                    {
                        audio_id_fonct = "ID";
                        msg = "";
                        msg += " Enter N° ID & =";
                        msg += "|0 = all";
                    }
                    else if (audio_id_fonction == 1)
                    {
                        audio_id_fonct = "CH";
                        msg = "";
                        msg += " Enter N° CH & =";
                        msg += "|0 = all";
                    }

                    ez.msgBox("M5 REMOTE AUDIO", msg, "## func|"+audio_id_fonct + "###Back", false);
                    draw_loop();
                    draw_volume();
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "## func|"+audio_id_fonct + "###Back", false);
                    draw_loop();
                    draw_volume();
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW LOOP///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_loop()
{
    if (mqtt_loop)
    {
        m5.lcd.setTextColor(TFT_RED);
        ez.setFont(ez.theme->menu_big_font);
        m5.lcd.setTextDatum(TR_DATUM);
        int16_t text_h = ez.fontHeight();
        m5.lcd.drawString("loop", TFT_W - ez.theme->input_hmargin, 10 + ez.theme->input_vmargin + text_h + 10);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////DRAW VOLUME/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void draw_volume()
{
    m5.lcd.setTextColor(TFT_WHITE);
    ez.setFont(ez.theme->menu_big_font);
    m5.lcd.setTextDatum(TR_DATUM);
    int16_t text_h = ez.fontHeight();
    m5.lcd.drawString("Volume:" + String(Volume), 10, 10 + ez.theme->input_vmargin + text_h + 10);
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////CHECK_FONCTION///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void check_fonction()
{
    audio_fonction += 1;
    if (audio_fonction >= 17)
    {
        audio_fonction = 0;
    }
    String val_fonc = String(audio_fonction);
    fonct = "Bank " + val_fonc;

    ez.msgBox("M5 REMOTE AUDIO", fonct, "id|"+id_cal + "# Menu #" + "bank|"+fonct + "# bankval|Val #" + "page|"+page_me + "# pageval|Val ", false);
    draw_loop();
    draw_volume();
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////CHECK_PAGE_MEM///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void check_page_mem()
{
    page_mem += 1;
    if (page_mem >= 13)
    {
        page_mem = 0;
    }
    String add_page = String(page_mem);
    if (page_mem < 12)
    {
        page_me = add_page + "0-" + add_page + "9";
    }
    else if (page_mem == 12)
    {
        page_me = add_page + "0-" + add_page + "7";
    }

    ez.msgBox("M5 REMOTE AUDIO", "Note " + page_me, "id|"+id_cal + "# Menu #" + "bank|"+fonct + "# bankval|Val #" + "page|"+page_me + "# pageval|Val ", false);
    draw_loop();
    draw_volume();
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////AUDIO_MASTER_VALUE///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool audio_master_value()
{
    bool bad = false;
    bool _a_b = true;
    String action = "";
    String res_value = "";
    String msg = "";
    int res;

    msg += " Enter value to master 0 -> 127 & =";
    ez.msgBox("M5 REMOTE AUDIO", msg, "#####Back", false);
    draw_loop();
    draw_volume();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        if (action == "Back") return false;

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

                    if (res < 128)
                    {
                        Volume = res_value.toInt();
                        send_volume();
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to master 0 -> 127 & =";
                        ez.msgBox("M5 REMOTE AUDIO", msg, "#####Back", false);
                        draw_loop();
                        draw_volume();
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
                    msg += " Enter value to master 0 -> 127 & =";
                    ez.msgBox("M5 REMOTE AUDIO", msg, "#####Back", false);
                    draw_loop();
                    draw_volume();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "#####Back", false);
                    draw_loop();
                    draw_volume();
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////PAGE_MEM_VALUE///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
bool page_mem_value()
{
    bool bad = false;
    String res_value = "";
    String msg = "";
    int res;

    msg += " Enter value to Page | 0 -> 12 & = ";
    msg += "| 0 = 0-9 .... 12 = 120-127 ";
    ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
    draw_loop();
    draw_volume();

    while (true)
    {
        ez.yield();

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

                    if (res < 13)
                    {
                        page_mem = res - 1;
                        return true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to Page | 0 -> 12 & = ";
                        msg += "| 0 = 0-9 .... 12 = 120-127 ";
                        ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
                        draw_loop();
                        draw_volume();
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
                    msg += " Enter value to Page | 0 -> 12 & = ";
                    msg += "| 0 = 0-9 .... 12 = 120-127 ";
                    ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
                    draw_loop();
                    draw_volume();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "#####", false);
                    draw_loop();
                    draw_volume();
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FONCTION_VALUE///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void fonction_value()
{
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";
    int res;

    msg += " Enter value to Bank | 0 -> 16 & = ";
    ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
    draw_loop();
    draw_volume();

    while (equal != true)
    {
        ez.yield();

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

                    if (res < 17)
                    {
                        audio_fonction = res - 1;
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to Bank | 0 -> 16 & = ";
                        ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
                        draw_loop();
                        draw_volume();
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
                    msg += " Enter value to Bank | 0 -> 16 & = ";
                    ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
                    draw_loop();
                    draw_volume();

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                {
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "#####", false);
                    draw_loop();
                    draw_volume();
                }
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////REMOTE_AUDIO/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void remote_audio()
{
    uint32_t _widget_time = millis();
    String action = "";
    bool _a_b = true;
    audio_mqtt_topic = String(MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_NOTEON);
    audio_mqtt_topic.toCharArray(audio_mqtt_topic_c, audio_mqtt_topic.length() + 1);

    ez.msgBox("M5 REMOTE AUDIO", "Welcome", "id|"+id_cal + "# Menu #" + "bank|"+fonct + "# bankval|Val #" + "page|"+page_me + "# pageval|Val ", false);
    draw_loop();
    draw_volume();

    while (true)
    {
        // Check Buttons
        action = ez.buttons.poll();

        if (action == "Menu") break;

        if (action == "id")
        {
            id_value_audio();

            ez.msgBox("M5 REMOTE AUDIO", id_cal, "id|"+id_cal + "# Menu #" + "bank|"+fonct + "# bankval|Val #" + "page|"+page_me + "# pageval|Val ", false);
            draw_loop();
            draw_volume();
        }

        if (action == "bankval")
        {
            fonction_value();
            check_fonction();
        }

        if (action == "bank")
        {
            check_fonction();
        }

        if (action == "pageval")
        {
            page_mem_value();
            check_page_mem();
        }

        if (action == "page")
        {
            check_page_mem();
        }

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

                    audio_mqtt_topic = String(MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_NOTEON);
                    audio_mqtt_topic.toCharArray(audio_mqtt_topic_c, audio_mqtt_topic.length() + 1);
                    audio_mqtt_message = String(audio_fonction) + "|" + String(page_mem + msg) + "|" + String(Volume) + "|" + String(mqtt_loop);
                    audio_mqtt_message.toCharArray(AUDIO_MQTT_MESSAGE, audio_mqtt_message.length() + 1);
                    ez.mqtt32->publish(audio_mqtt_topic_c, AUDIO_MQTT_MESSAGE, 1);
                    msg += "|" + audio_mqtt_topic + "|" + (page_mem + msg);

                    break;

                case '.':
                    audio_mqtt_topic = String(MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_STOP);
                    audio_mqtt_topic.toCharArray(audio_mqtt_topic_c, audio_mqtt_topic.length() + 1);
                    ez.mqtt32->publish(audio_mqtt_topic_c, nullptr, 1);
                    msg += "|" + audio_mqtt_topic;
                    break;
                case '=':
                    audio_master_value();
                    msg = "Volume " + _Volu + " SEND";
                    break;
                case '-':
                    Volume -= 2;
                    if (Volume < 0)
                    {
                        Volume = 0;
                    }
                    send_volume();
                    msg += "|" + audio_mqtt_topic + "|" + _Volu.c_str();
                    break;
                case '+':
                    Volume += 2;
                    if (Volume > 127 || Volume < 0)
                    {
                        Volume = 127;
                    }
                    send_volume();
                    msg += "|" + audio_mqtt_topic + "|" + _Volu.c_str();
                    break;

                case 'A':
                    Volume = 127;
                    send_volume();
                    msg += "|" + audio_mqtt_topic + "|" + _Volu.c_str();
                    break;

                case 'M':
                    audio_mqtt_topic = String(MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FADE_IN);
                    audio_mqtt_topic.toCharArray(audio_mqtt_topic_c, audio_mqtt_topic.length() + 1);
                    ez.mqtt32->publish(audio_mqtt_topic_c, nullptr, 1);
                    msg += "|" + audio_mqtt_topic;
                    break;

                case '%':
                    audio_mqtt_topic = String(MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FADE_OUT);
                    audio_mqtt_topic.toCharArray(audio_mqtt_topic_c, audio_mqtt_topic.length() + 1);
                    ez.mqtt32->publish(audio_mqtt_topic_c, nullptr, 1);
                    msg += "|" + audio_mqtt_topic;
                    break;

                case '/':
                    Volume -= 10;
                    if (Volume < 0)
                    {
                        Volume = 0;
                    }
                    send_volume();
                    msg += "|" + audio_mqtt_topic + "|" + _Volu.c_str();
                    break;

                case '*':
                    Volume += 10;
                    if (Volume > 127 || Volume < 0)
                    {
                        Volume = 127;
                    }
                    send_volume();
                    msg += "|" + audio_mqtt_topic + "|" + _Volu.c_str();
                    break;

                case '`':
                    mqtt_loop = !mqtt_loop;
                    draw_loop();
                    draw_volume();
                    if (mqtt_loop)
                    {
                        msg += "| LOOP ON";
                    }
                    else
                    {
                        msg += "| LOOP OFF";
                    }

                    break;

                } //switch case

                LOG(msg);
                ez.msgBox("M5 REMOTE AUDIO", msg, "id|"+id_cal + "# Menu #" + "bank|"+fonct + "# bankval|Val #" + "page|"+page_me + "# pageval|Val ", false);
                draw_loop();
                draw_volume();
            } //while wire

        } //digitale read

    } //while true

} //

#endif