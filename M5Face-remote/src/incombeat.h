void incombeat(char *payload, size_t length)
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

    for (int k = 0; k < count; k++)
    {
        if (T_ID[k] == result)
        {
            check = true;

        }
    }
    if (count + 1 <= max_clients && check != true)
    {
        clients += 1;
        if (clients <= max_clients)
        {

        }
        else
        {
            LOG("***************CLIENTS MAX");
        }
        check = false;
    }
}