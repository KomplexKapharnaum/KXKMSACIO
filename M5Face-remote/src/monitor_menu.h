#ifndef MONITOR_MENU_H
#define MONITOR_MENU_H

void menu_monitor();
void mon_id_menu();

int16_t who_result;

void monitor_menu()
{
    ez.mqtt.mqtt_on = ez.mqtt32->isConnected();

    who_result = 0;
    String on_off_line;

    if (clients == -1)
    {
        ezMenu monitor_menu("NO ESP");
        ez.msgBox("NO ESP", "NO ESP FOUND", "#Back####", true);
        monitor_menu.run();
    }
    else
    {
        ezMenu monitor_menu("ESP find");
        monitor_menu.upOnFirst("last|up");
        monitor_menu.downOnLast("first|down");
        monitor_menu.buttons("up#Back#select##down#");

        for (int k = 0; k <= clients; k++)
        {
            int beatresult = atoi(T_ID[k].c_str());
            for (int j = 0; j < max_clients; j++)
            {
                if (T_inlife[j][0] == beatresult)
                {
                    currentTime = millis();
                    previousTime = T_inlife[j][1];
                    if ((currentTime - previousTime) < 15000)
                    {
                        on_off_line = " ON Line";
                    }
                    else if ((currentTime - previousTime) > 15000)
                    {
                        on_off_line = " ... .. .";
                        T_inlife[j][2] = 0;
                    }
                }
            }

            monitor_menu.addItem(String(k) + " ESP : " + String(T_ID[k]) + on_off_line);
        }

        while (monitor_menu.runOnce())
        {
            who_result = monitor_menu.pick();
            if (who_result > 0)
                mon_id_menu();
        }
        monitor_menu.run();
    }
}

void mon_id_menu()
{
    String msg;
    int16_t m = who_result - 1;

    ezMenu mon_id_menu("ESP MONITOR");
    mon_id_menu.txtBig();
    msg += "Esp " + T_ID[m] + " | Channel " + T_CHA[m] + " | Version " + T_VER[m];
    msg += " | IP " + T_IP[m] + " | Reception " + T_WIF[m] + " db | Batterie " + T_BAT[m] + " %";
    msg += " | Playeur " + T_RUN[m];
    ez.msgBox("ESP MONITOR", msg, "up#Back#OK##down#", true);

    mon_id_menu.run();
}

#endif