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
    
    k32->remote->setState(REMOTE_AUTO);
    k32->remote->lock();

    if (k32->system->hw() == 3)
        pinMode(39, INPUT_PULLUP);
}

void boutons_loop()
{
    //////////////////     Click on ESP   ////////////////////
    if (k32->system->stm32->clicked())
    {
        k32->remote->stmNext();
    }

    //////////////////    Click on Atom    ////////////////////
    if (k32->system->hw() == 3)
    {
        int btn = digitalRead(39);
        if (didChange(W_ATOMBTN, btn) && btn == 0)
            k32->remote->stmNext();
    }

    //////////////////////  REMOTE CONTROL   ///////////////////////////

    // ACTIVE Macro
    int activeMacro = k32->remote->getActiveMacro();
    if (didChange(W_ACTIVEMACRO, activeMacro))
    {
        LOGF("REMOTE: -> set Active Macro = %d\n", activeMacro);

        load_mem( k32->light->anim("manu"), activeMacro );
    }

    // PREVIEW Macro
    int previewMacro = k32->remote->getPreviewMacro();
    if (didChange(W_PREVMACRO, previewMacro))
    {
        LOGF("REMOTE: -> set Preview Macro = %d\n", previewMacro);

        k32->light->anim("preview")->push(MEM_PREV[previewMacro], LULU_PREVPIX * 4);
    }

    // STATE Changed
    remoteState stateR = k32->remote->getState();
    if (didChange(W_STATE, stateR))
    {
        // AUTO
        if (stateR == REMOTE_AUTO)
        {
            k32->light->anim("manu")->stop();
            k32->light->anim("preview")->stop();
            k32->light->anim("artnet-sk")->play();
            k32->light->anim("artnet-dmx")->play();
            LOG("REMOTE: -> Mode AUTO");
        }

        // STM
        else if (stateR == REMOTE_MANU_STM)
        {
            k32->light->anim("artnet-sk")->stop();
            k32->light->anim("artnet-dmx")->stop();
            k32->light->anim("preview")->play();
            k32->light->anim("manu")->play();
            LOG("REMOTE: -> Mode STM");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            k32->light->anim("preview")->play();
            LOG("REMOTE: -> Mode MANU");
        }
    }

    // GO Active Macro
    if (k32->remote->getSendMacro())
        if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LAMP)
        {
            k32->light->anim("artnet-sk")->stop();
            k32->light->anim("artnet-dmx")->stop();
            k32->light->anim("manu")->play();
            LOG("REMOTE: -> MANU -> GO Macro !");
        }

    // LAMP
    int lamp = k32->remote->getLamp();
    if (didChange(W_LAMP, lamp))
    {
        if (lamp >= 0) {
            // k32->pwm->set(0, lamp);
            // k32->pwm->set(1, lamp);
        }
        else
        {
            k32->light->anim("artnet-sk")->push();
            k32->light->anim("artnet-dmx")->push();
            k32->light->anim("manu")->push();
        }
        LOGF("REMOTE: -> getLAMP @%d\n", lamp);
    }

} // void boutons();

#endif