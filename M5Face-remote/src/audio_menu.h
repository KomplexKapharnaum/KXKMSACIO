void check_page_mem();
void check_fonction();
void remote_audio();
void audio_master_value();
void page_mem_value();
void fonction_value();

uint8_t page_mem = 0;
String page_me = "00-09";
uint8_t id_call = 0;
String id_cal = "all";
uint8_t fonction = 0;
String fonct = "Bank 0";
uint8_t volu = 127;

// int16_t who_result;
String id_calling = "";
String volume = "127";

uint8_t id_fonction = 0;
String id_fonct = "ID";

char AUDIO_MQTT_TOPIC[] = "k32/all";
char AUDIO_MQTT_MESSAGE[] = "";
String audio_mqtt_topic;
String audio_mqtt_message;
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
String AUDIO_MQTT_FADE_IN = "/volume/fadein";
String AUDIO_MQTT_FADE_OUT = "/volume/fadeout";

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////CHECK_FONCTION///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void check_fonction()
{
    fonction += 1;
    if (fonction >= 17)
    {
        fonction = 0;
    }
    String val_fonc = String(fonction);
    fonct = "Bank " + val_fonc;

    ez.msgBox("M5 REMOTE AUDIO", fonct, id_cal + "# Menu #" + fonct + "# Val. #" + page_me + "# Val. ", false);
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

    ez.msgBox("M5 REMOTE AUDIO", "Note " + page_me, id_cal + "# Menu #" + fonct + "# Val. #" + page_me + "# Val. ", false);
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////AUDIO_MASTER_VALUE///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void audio_master_value()
{
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";
    int res;

    msg += " Enter value to master 0 -> 127 & =";
    ez.msgBox("M5 REMOTE AUDIO", msg, "#####Back", false);

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            remote_audio();
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

                    if (res < 128)
                    {
                        volu = res_value.toInt();
                        LOG("volu = ");
                        LOG(volu);
                        volume = (res_value).c_str();
                        audio_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(AUDIO_MQTT_VOLUME);
                        audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                        k32->mqtt->publish(AUDIO_MQTT_TOPIC, (res_value).c_str(), 1);
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to master 0 -> 127 & =";
                        ez.msgBox("M5 REMOTE AUDIO", msg, "#####Back", false);
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

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "#####Back", false);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////PAGE_MEM_VALUE///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void page_mem_value()
{
    bool equal = false;
    bool bad = false;
    String res_value = "";
    String msg = "";
    int res;

    msg += " Enter value to Page | 0 -> 12 & = ";
    msg += "| 0 = 0-9 .... 12 = 120-127 ";
    ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        // if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        // {
        //     remote_audio();
        // };

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
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to Page | 0 -> 12 & = ";
                        msg += "| 0 = 0-9 .... 12 = 120-127 ";
                        ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
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

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "#####", false);
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

    while (equal != true)
    {
        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        // if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        // {
        //     remote_audio();
        // };

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
                        fonction = res - 1;
                        equal = true;
                    }
                    else
                    {
                        bad = true;
                        res_value = "";
                        msg = "";
                        msg += " Enter value to Bank | 0 -> 16 & = ";
                        ez.msgBox("M5 REMOTE AUDIO", msg, "#####", false);
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

                    break;
                case 'M':

                    break;
                case '%':

                    break;
                }
                LOG(value);
                if (bad != true)
                    ez.msgBox("M5 REMOTE AUDIO", res_value, "#####", false);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////REMOTE_AUDIO/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void remote_audio()
{

    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_PLAY);
    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);

    ez.msgBox("M5 REMOTE AUDIO", "Welcome", id_cal + "# Menu #" + fonct + "# Val. #" + page_me + "# Val. ", false);

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
                ez.msgBox("M5 REMOTE AUDIO", id_cal, id_cal + "# Menu #" + fonct + "# Val. #" + page_me + "# Val. ", false);
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
                ez.msgBox("M5 REMOTE AUDIO", id_cal, id_cal + "# Menu #" + fonct + "# Val. #" + page_me + "# Val. ", false);
            }
            audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_PLAY);
            audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
        };

        if (m5.BtnB.pressedFor(ez.theme->longpress_time))
        {
            fonction_value();
            check_fonction();
        };

        if (M5.BtnB.wasReleased())
        {
            check_fonction();
        };

        if (m5.BtnC.pressedFor(ez.theme->longpress_time))
        {
            page_mem_value();
            check_page_mem();
        };

        if (M5.BtnC.wasReleased())
        {
            check_page_mem();
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

                    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_NOTEON);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    audio_mqtt_message = String(fonction) + "§" + String(page_mem + msg) + "§" + String(volu);
                    audio_mqtt_message.toCharArray(AUDIO_MQTT_MESSAGE, audio_mqtt_message.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, AUDIO_MQTT_MESSAGE, 1);
                    msg += " " + audio_mqtt_topic + (page_mem + msg);

                    break;

                case '.':
                    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_STOP);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                case '=':
                    audio_master_value();
                    msg = "Volume " + volume + " SEND";
                    break;
                case '-':
                    volu = volu - 2;
                    if (volu < 0)
                    {
                        volu = 0;
                    }
                    LOG("volu = ");
                    LOG(volu);
                    volume = String(volu);
                    LOG("volume = ");
                    LOG(volume);
                    audio_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(AUDIO_MQTT_VOLUME);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, volume.c_str(), 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                case '+':
                    volu = volu + 2;
                    if (volu > 128)
                    {
                        volu = 127;
                    }
                    LOG("volu = ");
                    LOG(volu);
                    volume = String(volu);
                    LOG("volume = ");
                    LOG(volume);
                    audio_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(AUDIO_MQTT_VOLUME);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, volume.c_str(), 1);
                    msg += " " + audio_mqtt_topic;
                    break;

                case 'A':
                    volu = 127;
                    volume = String(volu);
                    audio_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(AUDIO_MQTT_VOLUME);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, volume.c_str(), 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                case 'M':
                    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FADE_IN);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                case '%':
                    audio_mqtt_topic = String(AUDIO_MQTT_K32) + String(AUDIO_MQTT_ID) + String(AUDIO_MQTT_FADE_OUT);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, nullptr, 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                case '/':
                    volu = volu - 10;
                    if (volu < 0)
                    {
                        volu = 0;
                    }
                    volume = String(volu);
                    audio_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(AUDIO_MQTT_VOLUME);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, volume.c_str(), 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                case '*':
                    volu = volu + 10;
                    if (volu > 128)
                    {
                        volu = 127;
                    }
                    volume = String(volu);
                    audio_mqtt_topic = String(MQTT_K32) + String(MQTT_ID) + String(AUDIO_MQTT_VOLUME);
                    audio_mqtt_topic.toCharArray(AUDIO_MQTT_TOPIC, audio_mqtt_topic.length() + 1);
                    k32->mqtt->publish(AUDIO_MQTT_TOPIC, volume.c_str(), 1);
                    msg += " " + audio_mqtt_topic;
                    break;
                }
                LOG(msg);
                ez.msgBox("M5 REMOTE AUDIO", msg, id_cal + "# Menu #" + fonct + "# Val. #" + page_me + "# Val. ", false);
            }
        }
    }
}