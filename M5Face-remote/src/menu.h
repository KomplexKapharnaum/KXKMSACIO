
void mainmenu_mqtt()
{
    uint8_t fonction = 0;
    String fonct = "Master";
    uint8_t page_mem = 0;
    String page_me = "0-9";
    ez.msgBox("M5 MQTT", "Welcome", "menu #" + fonct + "#" + page_me, false);

    while (true)
    {

        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (m5.BtnA.pressedFor(ez.theme->longpress_time))
        {
            break;
        };

        if (M5.BtnB.wasPressed())
        {
            fonction += 1;
            if (fonction >= 2)
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

            ez.msgBox("M5 MQTT", fonct, "menu #" + fonct + "#" + page_me, false);
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
            ez.msgBox("M5 MQTT", page_me, "menu #" + fonct + "#" + page_me, false);
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
                    k32->mqtt->publish("k32/all/leds/mem", (page_mem + msg).c_str(), 1);
                    msg += " k32/all/leds/mem " + (page_mem + msg);
                    break;

                case '.':
                    k32->mqtt->publish("k32/all/leds/stop", nullptr, 1);
                    msg += " k32/all/leds/stop";
                    break;
                case '=':
                    if (fonction == 0)
                    {
                        k32->mqtt->publish("k32/all/leds/master/fadeout", nullptr, 1);
                        msg += " k32/all/leds/master/fadeout";
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '-':
                    if (fonction == 0)
                    {
                        k32->mqtt->publish("k32/all/leds/master/less", nullptr, 1);
                        msg += " k32/all/leds/master/less";
                    }
                    else if (fonction == 1)
                    {
                        k32->mqtt->publish("k32/all/leds/mod/slower", nullptr, 1);
                        msg += " k32/all/leds/mod/slower";
                    }
                    break;
                case '+':
                    if (fonction == 0)
                    {
                        k32->mqtt->publish("k32/all/leds/master/more", nullptr, 1);
                        msg += " k32/all/leds/master/more";
                    }
                    else if (fonction == 1)
                    {
                        k32->mqtt->publish("k32/all/leds/mod/faster", nullptr, 1);
                        msg += " k32/all/leds/mod/faster";
                    }
                    break;

                case 'A':
                    if (fonction == 0)
                    {
                        k32->mqtt->publish("k32/all/leds/master/full", nullptr, 1);
                        msg += " k32/all/leds/mem/full";
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case 'M':
                    if (fonction == 0)
                    {
                        k32->mqtt->publish("k32/all/leds/master/fadein", nullptr, 1);
                        msg += " k32/all/leds/mem/fadein";
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '%':
                    if (fonction == 0)
                    {
                        k32->mqtt->publish("k32/all/leds/master/fadeout", nullptr, 1);
                        msg += " k32/all/leds/mem/fadeout";
                    }
                    else if (fonction == 1)
                    {
                    }
                    break;
                case '/':
                    if (fonction == 0)
                    {
                    }
                    else if (fonction == 1)
                    {
                    }
                }
                LOG(msg);
                ez.msgBox("M5 MQTT", msg, "menu #" + fonct + "#" + page_me, false);
            }
        }
    }
}

void powerOff() { m5.powerOFF(); }

void mainmenu()
{
    ezMenu mainmenu("Welcome to M5");
    mainmenu.txtBig();
    mainmenu.addItem("MQTT", mainmenu_mqtt);
    mainmenu.addItem("SET UP", ez.settings.menu);
    mainmenu.addItem("POWER OFF", powerOff);
    mainmenu.upOnFirst("last|up");
    mainmenu.downOnLast("first|down");
    mainmenu.run();
}