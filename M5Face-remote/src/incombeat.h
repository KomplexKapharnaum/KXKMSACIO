#ifndef INCOMBEAT_H
#define INCOMBEAT_H

void incombeat(char *payload, size_t length)
{
    currentTime = millis();
    bool check = false;
    int count;
    char input[strlen(payload)];
    strcpy(input, payload);
    char *ID_CHECK = strtok(input, "|");
    int beatresult = atoi(ID_CHECK);

    for (int k = 0; k < max_clients; k++)
    {
        if (T_inlife[k][0] == beatresult)
        {
            previousTime = T_inlife[k][1];
            if ((currentTime - previousTime) < 2500)
            {
                T_inlife[k][1] = currentTime;
                T_inlife[k][2] = 1;
                break;
            }
            else
            {
                T_inlife[k][1] = currentTime;
                T_inlife[k][2] = 0;
                break;
            }
        }
        else if (T_inlife[k][2] != 1)
        {
            T_inlife[k][0] = beatresult;
            T_inlife[k][1] = currentTime;
            T_inlife[k][2] = 1;
            break;
        }
    }
}

#endif