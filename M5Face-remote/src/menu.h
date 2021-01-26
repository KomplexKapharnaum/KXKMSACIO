int16_t who_result;

void mainmenu_mqtt()
{
    uint8_t fonction = 0;
    String fonct = "Master";
    uint8_t page_mem = 0;
    String page_me = "0-9";
    ez.msgBox("M5 REMOTE", "Welcome", "# Menu #" + fonct + "##" + page_me + "#", false);

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

            ez.msgBox("M5 REMOTE", fonct, "# Menu #" + fonct + "##" + page_me + "#", false);
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
            ez.msgBox("M5 REMOTE", page_me, "# Menu #" + fonct + "##" + page_me + "#", false);
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
                ez.msgBox("M5 REMOTE", msg, "# Menu #" + fonct + "##" + page_me + "#", false);
            }
        }
    }
}

void powerOff() { m5.powerOFF(); }

void mainmenu_mon_id()
{
    String msg;
    int16_t m = who_result;
    // LOGINL("************MON ID******  ");
    // LOGINL(" id = ");
    // LOG(m);
    // LOGINL(" who = ");
    // LOG(who_result);

    ezMenu mainmenu_mon_id("ESP MONITOR");
    mainmenu_mon_id.txtBig();
    msg += "Esp " + T_ID[m] + " | Channel " + T_CHA[m] + " | Version " + T_VER[m];
    msg += " | IP " + T_IP[m] + " | Reception " + T_WIF[m] + " db | Batterie " + T_BAT[m] + " %";
    msg += " | Playeur " + T_RUN[m];
    ez.msgBox("ESP MONITOR", msg, "up#Back#OK##down#", true);

    mainmenu_mon_id.run();
}

void mainmenu_monitor()
{
    who_result = 0;

    if (clients == 0)
    {
        ezMenu mainmenu_monitor("NO ESP");
        ez.msgBox("NO ESP", "NO ESP FOUND", "#Back####", true);
        mainmenu_monitor.run();
    }
    else
    {
        ezMenu mainmenu_monitor("ESP find");
        mainmenu_monitor.upOnFirst("last|up");
        mainmenu_monitor.downOnLast("first|down");
        mainmenu_monitor.buttons("up#Back#select##down#");

        for (int k = 1; k < clients; k++)
        {
            mainmenu_monitor.addItem(String(k) + " ESP : " + String(T_ID[k]));
        }

        while (mainmenu_monitor.runOnce())
        {
            who_result = mainmenu_monitor.pick();
            if (who_result > 0)
                mainmenu_mon_id();
        }
        mainmenu_monitor.run();
    }
}

void mainmenu()
{
    ezMenu mainmenu("Welcome to M5");
    mainmenu.txtBig();
    mainmenu.addItem("REMOTE", mainmenu_mqtt);
    mainmenu.addItem("MONITOR", mainmenu_monitor);
    mainmenu.addItem("SET UP", ez.settings.menu);
    mainmenu.addItem("POWER OFF", powerOff);
    mainmenu.upOnFirst("last|up");
    mainmenu.downOnLast("first|down");
    mainmenu.run();
}