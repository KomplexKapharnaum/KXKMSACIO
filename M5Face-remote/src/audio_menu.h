void remote_audio();

// int16_t who_result;
String id_calling = "";

uint8_t id_fonction = 0;
String id_fonct = "ID";

char AUDIO_MQTT_TOPIC[] = "k32/all/leds";
String audio_mqtt_topic;
String AUDIO_MQTT_ID = "all";
String AUDIO_MQTT_K32 = "k32/";
String AUDIO_MQTT_PLAY = "/play";
String AUDIO_MQTT_NOTEON = "/noteon";
String AUDIO_MQTT_NOTEOFF = "/noteoff";
String AUDIO_MQTT_STOP = "/stop";
String AUDIO_MQTT_VOLUME = "/volume";
String AUDIO_MQTT_LOOP = "/loop";
String AUDIO_MQTT_UNLOOP = "/unloop";
String AUDIO_MQTT_MIDI = "/midi";

// TODO
String AUDIO_MQTT_LESS = "/volume/less";
String AUDIO_MQTT_TENLESS = "/volume/tenless";
String AUDIO_MQTT_MORE = "/volume/more";
String AUDIO_MQTT_TENMORE = "/volume/tenmore";
String AUDIO_MQTT_FULL = "/volume/full";
String AUDIO_MQTT_FADE_IN = "/volume/fadein";
String AUDIO_MQTT_FADE_OUT = "/volume/fadeout";

void remote_audio()
{
    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_PLAY);
    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
    uint8_t id_call = 0;
    String id_cal = "all";
    uint8_t fonction = 0;
    String fonct = "Master";
    uint8_t page_mem = 0;
    String page_me = "0-9";
    ez.msgBox("M5 REMOTE AUDIO", "Welcome", id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);

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
                AUDIO_MQTT_ID = "all";
                ez.msgBox("M5 REMOTE AUDIO", id_cal, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
            }
            else if (id_call == 1)
            {
                id_value();
                if (id_fonction == 0)
                {
                    id_cal = "id" + id_calling;
                }
                else if (id_fonction == 1)
                {
                    id_cal = "ch" + id_calling;
                }
                ez.msgBox("M5 REMOTE AUDIO", id_cal, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
            }
            audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_PLAY);
            audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
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

            ez.msgBox("M5 REMOTE AUDIO", fonct, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
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
            ez.msgBox("M5 REMOTE AUDIO", page_me, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
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
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_PLAY);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, (page_mem + msg).c_str(), 1);
                        msg += " " + audio_mqtt_topic + (page_mem + msg);
                    }
                    else if (fonction == 2)
                    {
                        if ((char)key_val == '0')
                        {
                        }
                        else if ((char)key_val == '1')
                        {
                        }
                        else if ((char)key_val == '2')
                        {
                        }
                        else if ((char)key_val == '3')
                        {
                        }
                        else if ((char)key_val == '4')
                        {
                        }
                        else if ((char)key_val == '5')
                        {
                        }
                        else if ((char)key_val == '6')
                        {
                        }
                        else if ((char)key_val == '7')
                        {
                        }
                        else if ((char)key_val == '8')
                        {
                        }
                        else if ((char)key_val == '9')
                        {
                        }
                    }
                    break;

                case '.':
                    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_STOP);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                    msg += " " + audio_mqtt_topic;
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
                    }
                    break;
                case '-':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_LESS);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '+':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_MORE);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;

                case 'A':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FULL);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case 'M':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FADE_IN);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '%':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FADE_OUT);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '/':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_TENLESS);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    else if (fonction == 2)
                    {
                    }
                    break;
                case '*':
                    if (fonction == 0)
                    {
                        audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_TENMORE);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                        msg += " " + audio_mqtt_topic;
                    }
                    else if (fonction == 1)
                    {
                    }
                    else if (fonction == 2)
                    {
                    }
                    break;
                }
                LOG(msg);
                ez.msgBox("M5 REMOTE AUDIO", msg, id_cal + "# Menu #" + fonct + "##" + page_me + "#", false);
            }
        }
    }
}