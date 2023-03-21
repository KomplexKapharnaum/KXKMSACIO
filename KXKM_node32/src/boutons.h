/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  BOUTONS   ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#ifndef boutons_h
#define boutons_h

#define WATCH_SLOTS 8

enum watchSlot
{
    W_STATE,
    W_PREVMACRO,
    W_ACTIVEMACRO,
    W_LAMP,
    W_ATOMBTN
};

static int watchValues[WATCH_SLOTS];

bool didChange(watchSlot k, int value)
{
    if (k < WATCH_SLOTS && watchValues[k] != value)
    {
        watchValues[k] = value;
        return true;
    }
    return false;
}

void boutons_init()
{
    for (int i = 0; i < WATCH_SLOTS; i++)
        watchValues[i] = -128;

    if (k32->system->hw() >= 13)
        pinMode(39, INPUT_PULLUP);
}

void boutons_loop()
{
    //////////////////    Click on Atom    ////////////////////
    if (k32->system->hw() >= 13 )
    {
        int btn = digitalRead(39);
        if (didChange(W_ATOMBTN, btn) && btn == 0)
            k32->emit("btn/atom");
    }

} // void boutons();

#endif