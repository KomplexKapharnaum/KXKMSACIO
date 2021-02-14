
void remote_lulu();

void master_value();
void id_value();
void color_value();

String MQTT_ID = "all";
String MQTT_K32 = "k32/";

int16_t who_result;
String light_id_calling = "";

uint8_t light_id_fonction = 0;
String light_id_fonct = "ID";

uint8_t red, green, blue, white;
String light_mqtt_color;
char LIGHT_MQTT_COLOR[] = "0";

char LIGHT_MQTT_TOPIC[] = "k32/all/leds";
String light_mqtt_topic;
String LIGHT_MQTT_MEM = "/leds/mem";
String LIGHT_MQTT_STOP = "/leds/stop";
String LIGHT_MQTT_LESS = "/leds/master/less";
String LIGHT_MQTT_TENLESS = "/leds/master/tenless";
String LIGHT_MQTT_SLOWER = "/leds/mod/slower";
String LIGHT_MQTT_SMALLER = "/leds/mod/smaller";
String LIGHT_MQTT_MORE = "/leds/master/more";
String LIGHT_MQTT_TENMORE = "/leds/master/tenmore";
String LIGHT_MQTT_FASTER = "/leds/mod/faster";
String LIGHT_MQTT_BIGGER = "/leds/mod/bigger";
String LIGHT_MQTT_FULL = "/leds/master/full";
String LIGHT_MQTT_FADE_IN = "/leds/master/fadein";
String LIGHT_MQTT_FADE_OUT = "/leds/master/fadeout";
String LIGHT_MQTT_MASTER = "/leds/master";
String LIGHT_MQTT_COLOR_ALL = "/leds/all";
String LIGHT_MQTT_COLOR_STRIP = "/leds/strip";
String LIGHT_MQTT_COLOR_PIXEL = "/leds/pixel";

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

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            remote_lulu();
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
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                    ez.msgBox("M5 REMOTE LIGHT", res_value, "##" + color_fonct + "###Back", false);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////ID6_VALUE//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void id_value()
{
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";

    msg += " Enter N° ID & =";
    ez.msgBox("M5 REMOTE LIGHT", msg, "##" + light_id_fonct + "###Back", false);

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            remote_lulu();
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
                    bad = true;

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                if (bad != true)
                    ez.msgBox("M5 REMOTE LIGHT", res_value, "##" + light_id_fonct + "###Back", false);
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

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            remote_lulu();
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
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MASTER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, (res_value).c_str(), 1);
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to master 0 -> 255 & =";
                        ez.msgBox("M5 REMOTE LIGHT", msg, "#####Back", false);
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

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE LIGHT", res_value, "#####Back", false);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////REMOTE_LULU//////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void remote_lulu()
{
    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MEM);
    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
    uint8_t id_call = 0;
    String id_cal = "all";
    uint8_t fonction = 0;
    String fonct = "Master";
    uint8_t page_mem = 0;
    String page_me = "0-9";
    ez.msgBox("M5 REMOTE LIGHT", "Welcome", id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);

    while (true)
    {

        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (m5.BtnA.pressedFor(ez.theme->longpress_time))
        {
            break;
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
            }
            light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MEM);
            light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
        };

        if (M5.BtnB.wasPressed())
        {
            fonction += 1;
            if (fonction >= 3)
            {
                fonction = 0;
            }
            if (fonction == 0)
            {
                fonct = "Master";
            }
            else if (fonction == 1)
            {
                fonct = "Speed";
            }
            else if (fonction == 2)
            {
                fonct = "Color";
            }

            ez.msgBox("M5 REMOTE LIGHT", fonct, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
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
                    if (fonction < 2)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MEM);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, (page_mem + msg).c_str(), 1);
                        msg += " " + light_mqtt_topic + (page_mem + msg);
                    }
                    else if (fonction == 2)
                    {
                        if ((char)key_val == '0')
                        {
                            red = 23;
                            green = 23;
                            blue = 23;
                            white = 23;
                            msg += " DIA ALL ";
                        }
                        else if ((char)key_val == '1')
                        {
                            red = 255;
                            green = 0;
                            blue = 0;
                            white = 0;
                            msg += " RED ";
                        }
                        else if ((char)key_val == '2')
                        {
                            green = 255;
                            red = 0;
                            blue = 0;
                            white = 0;
                            msg += " GREEN ";
                        }
                        else if ((char)key_val == '3')
                        {
                            blue = 255;
                            red = 0;
                            green = 0;
                            white = 0;
                            msg += " BLUE ";
                        }
                        else if ((char)key_val == '4')
                        {
                            white = 255;
                            red = 0;
                            green = 0;
                            blue = 0;
                            msg += " WHITE ";
                        }
                        else if ((char)key_val == '5')
                        {
                            red = 255;
                            green = 127;
                            blue = 0;
                            white = 0;
                            msg += " ORANGE ";
                        }
                        else if ((char)key_val == '6')
                        {
                            red = 255;
                            green = 255;
                            blue = 0;
                            white = 0;
                            msg += " YELLOW ";
                        }
                        else if ((char)key_val == '7')
                        {
                            green = 255;
                            blue = 255;
                            red = 0;
                            white = 0;
                            msg += " CYAN ";
                        }
                        else if ((char)key_val == '8')
                        {
                            red = 255;
                            blue = 255;
                            green = 0;
                            white = 0;
                            msg += " MAGENTA ";
                        }
                        else if ((char)key_val == '9')
                        {
                            red = 255;
                            green = 255;
                            blue = 255;
                            white = 255;
                            msg += " FULL ALL ";
                        }
                        light_mqtt_color = String(red) + "| " + String(green) + "| " + String(blue) + "| " + String(white);
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_COLOR_ALL);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, light_mqtt_color.c_str(), 1);
                        msg += "|" + light_mqtt_topic + "|" + " " + light_mqtt_color;
                    }
                    break;

                case '.':
                    light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_STOP);
                    light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                    k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                    msg += " " + light_mqtt_topic;
                    break;
                case '=':
                    if (fonction == 0)
                    {
                        master_value();
                        msg = "Master SEND";
                    }
                    else if (fonction == 1)
                    {
                    }
                    else if (fonction == 2)
                    {
                        color_value();
                        light_mqtt_color = String(red) + "| " + String(green) + "| " + String(blue) + "| " + String(white);
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_COLOR_ALL);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, light_mqtt_color.c_str(), 1);
                        msg = "Color SEND";
                        msg += "|" + light_mqtt_topic + "|" + " " + light_mqtt_color;
                    }
                    break;
                case '-':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_LESS);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_SLOWER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    break;
                case '+':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_MORE);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FASTER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    break;

                case 'A':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FULL);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case 'M':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FADE_IN);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '%':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_FADE_OUT);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '/':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_TENLESS);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_SMALLER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 2)
                    {
                    }
                    break;
                case '*':
                    if (fonction == 0)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_TENMORE);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                        light_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(LIGHT_MQTT_BIGGER);
                        light_mqtt_topic.toCharArray(LIGHT_MQTT_TOPIC, light_mqtt_topic.length() + 1);
                        k32->mqtt->publish(LIGHT_MQTT_TOPIC, nullptr, 1);
                        msg += " " + light_mqtt_topic;
                    }
                    else if (fonction == 2)
                    {
                    }
                    break;
                }
                LOG(msg);
                ez.msgBox("M5 REMOTE LIGHT", msg, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
            }
        }
    }
}
