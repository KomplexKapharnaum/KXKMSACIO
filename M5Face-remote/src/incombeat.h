void incombeat(char *payload, size_t length)
{
    LOGINL("in beat");
    currentTime = millis();
    bool check = false;
    int count;
    char input[strlen(payload)];
    strcpy(input, payload);
    char *ID_CHECK = strtok(input, "§");
    int beatresult = atoi(ID_CHECK);

    // if ((currentTime - previousTime) > 3000)

    for (int k = 0; k < max_clients; k++)
    {
        if (T_inlife[k][0] == beatresult)
        {
            LOGINL(" == ");
            previousTime = T_inlife[k][1];
            if ((currentTime - previousTime) < 2500)
            {
                LOGINL(" < 2500 ");
                T_inlife[k][1] = currentTime;
                T_inlife[k][2] = 1;
                break;
            }
            else
            {
                LOGINL("ELSE  NOT < 2500 ");
                T_inlife[k][1] = currentTime;
                T_inlife[k][2] = 0;
                break;
            }
        }
        else if (T_inlife[k][2] != 1)
        {
            LOGINL(" != 1");
            T_inlife[k][0] = beatresult;
            T_inlife[k][1] = currentTime;
            T_inlife[k][2] = 1;
            break;
        }
    }
}