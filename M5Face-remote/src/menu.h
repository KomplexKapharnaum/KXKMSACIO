
void mainmenu_mqtt()
{

    ez.msgBox("M5 MQTT", "Welcome", "menu # master # up ", false);
    uint8_t fonction = 0;
    String fonct;
    uint8_t page_mem = 0;
    String page_me;

    while (true)
    {

        M5.update();

        // BTN A/B/C    || M5.BtnA.isPressed()
        //
        if (M5.BtnA.wasPressed())
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

            ez.msgBox("M5 MQTT", fonct, "menu #" + fonct + "# up ", false);
        };

        if (M5.BtnC.wasPressed() || M5.BtnC.isPressed())
        {
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
                    k32->mqtt->publish("k32/all/leds/mem", msg.c_str(), 1);
                    msg += " k32/all/leds/mem " + msg;
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
                    }
                    break;

                case 'A':
                    k32->mqtt->publish("/event/btn1");
                    msg += " /event/btn1";
                    break;
                case 'M':
                    k32->mqtt->publish("/event/btn2");
                    msg += " /event/btn2";
                    break;
                case '%':
                    k32->mqtt->publish("/event/btn3");
                    msg += " /event/btn3";
                    break;
                case '/':
                    k32->mqtt->publish("/event/btn4");
                    msg += " /event/btn4";
                    break;
                }
                LOG(msg);
                if (fonction == 0)
                    ez.msgBox("M5 MQTT", msg, "menu # Master # up ", false);
                else if (fonction == 1)
                    ez.msgBox("M5 MQTT", msg, "menu # Speed # up ", false);
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