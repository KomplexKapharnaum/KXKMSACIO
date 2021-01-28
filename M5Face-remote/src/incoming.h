

void update_tableau(char *payload, int num)
{
    // num -= 1;
    LOG("***************UPDATE******  ");
    int z = 0;
    char input[strlen(payload)];
    strcpy(input, payload);
    char *ID_CHECK = strtok(input, "§");
    while (ID_CHECK != NULL)
    {
        z += 1;
        if (z == 1)
        {
            LOGINL("num ");
            LOG(num);
            T_ID[num] = String(ID_CHECK);
            LOGINL("T_ID ");
            LOG(T_ID[num]);
        }
        else if (z == 2)
        {
            T_CHA[num] = String(ID_CHECK);
            LOGINL("T_CHA ");
            LOG(T_CHA[num]);
        }
        else if (z == 3)
        {
            T_VER[num] = String(ID_CHECK);
            LOGINL("T_VER ");
            LOG(T_VER[num]);
        }
        else if (z == 4)
        {
            T_MAC[num] = String(ID_CHECK);
            LOGINL("T_MAC ");
            LOG(T_MAC[num]);
        }
        else if (z == 5)
        {
            T_IP[num] = String(ID_CHECK);
            LOGINL("T_IP ");
            LOG(T_IP[num]);
        }
        else if (z == 6)
        {
            T_WIF[num] = String(ID_CHECK);
            LOGINL("T_WIF ");
            LOG(T_WIF[num]);
        }
        else if (z == 8)
        {
            T_BAT[num] = String(ID_CHECK);
            LOGINL("T_BAT ");
            LOG(T_BAT[num]);
        }
        else if (z == 10)
        {
            T_RUN[num] = String(ID_CHECK);
            LOGINL("T_RUN ");
            LOG(T_RUN[num]);
        }
        ID_CHECK = strtok(NULL, "§");
    }
}

void store_tableau(char *payload, int num)
{
    // num -= 1;
    LOG("***************STORE******  ");
    int z = 0;
    char input[strlen(payload)];
    strcpy(input, payload);
    char *ID_CHECK = strtok(input, "§");
    while (ID_CHECK != NULL)
    {
        z += 1;
        if (z == 1)
        {
            LOGINL("num ");
            LOG(num);
            T_ID[num] = String(ID_CHECK);
            LOGINL("T_ID ");
            LOG(T_ID[num]);
        }
        else if (z == 2)
        {
            T_CHA[num] = String(ID_CHECK);
            LOGINL("T_CHA ");
            LOG(T_CHA[num]);
        }
        else if (z == 3)
        {
            T_VER[num] = String(ID_CHECK);
            LOGINL("T_VER ");
            LOG(T_VER[num]);
        }
        else if (z == 4)
        {
            T_MAC[num] = String(ID_CHECK);
            LOGINL("T_MAC ");
            LOG(T_MAC[num]);
        }
        else if (z == 5)
        {
            T_IP[num - 1] = String(ID_CHECK);
            LOGINL("T_IP ");
            LOG(T_IP[num]);
        }
        else if (z == 6)
        {
            T_WIF[num - 1] = String(ID_CHECK);
            LOGINL("T_WIF ");
            LOG(T_WIF[num]);
        }
        else if (z == 8)
        {
            T_BAT[num - 1] = String(ID_CHECK);
            LOGINL("T_BAT ");
            LOG(T_BAT[num]);
        }
        else if (z == 10)
        {
            T_RUN[num] = String(ID_CHECK);
            LOGINL("T_RUN ");
            LOG(T_RUN[num]);
        }
        ID_CHECK = strtok(NULL, "§");
    }
}

void incoming(char *payload, size_t length)
{
    bool check = false;
    int count;
    char result[strlen(payload)];
    char input[strlen(payload)];
    strcpy(input, payload);
    char *ID_CHECK = strtok(input, "§");
    strcpy(result, ID_CHECK);

    if (clients <= max_clients)
    {
        count = clients;
    }
    else
    {
        count = max_clients;
    }

    if (count != -1)
    {
        for (int k = 0; k < count; k++)
        {
            if (T_ID[k] == result)
            {
                check = true;
                update_tableau(payload, k);
            }
        }
    }
    if (count + 1 <= max_clients && check != true)
    {
        clients += 1;
        if (clients <= max_clients)
        {
            store_tableau(payload, clients);
        }
        else
        {
            LOG("***************CLIENTS MAX");
        }
        check = false;
    }
}
