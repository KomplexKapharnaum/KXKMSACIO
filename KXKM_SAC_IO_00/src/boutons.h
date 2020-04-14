/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  BOUTONS   ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#ifndef boutons_h
#define boutons_h

#include "mem.h"



#define WATCH_SLOTS 8

enum watchSlot {
    W_STATE,
    W_PREVMACRO,
    W_ACTIVEMACRO,
    W_LAMP,
    W_ATOMBTN
};

static int watchValues[WATCH_SLOTS];

bool didChange(watchSlot k, int value) 
{
    if (k < WATCH_SLOTS && watchValues[k] != value) {
        watchValues[k] = value;
        return true;
    }
    return false;
}


void boutons_init() 
{
    for (int i=0; i<WATCH_SLOTS; i++) 
        watchValues[i] = -128;

    k32->remote->setState(REMOTE_AUTO_LOCK);

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
        if ( didChange(W_ATOMBTN, btn) && btn == 0) 
            k32->remote->stmNext();       
    }


    //////////////////////  REMOTE CONTROL   ///////////////////////////

    // ACTIVE Macro
    int activeMacro = k32->remote->getActiveMacro();
    if ( didChange(W_ACTIVEMACRO, activeMacro) ) 
    {   
        LOGF("REMOTE: -> set Active Macro = %d\n", activeMacro);

        K32_anim* manu = k32->light->anim("manu");

        // remove disposable modulators
        //
        manu->unmod();

        // push new data (from mem.h)
        //
        manu->push( MEM[ activeMacro ], LULU_PATCHSIZE );  
        
        // add modulators
        //
        if (activeMacro == 8) {
            manu->mod(new K32_mod_fadeout) ->at(0)->at(16)->at(17) ->period(5000);
        }
        else if (activeMacro == 10) {
            manu->mod(new K32_mod_sinus) ->at(15) ->period(1000);                      
        }
        else if (activeMacro == 11) {
            manu->mod(new K32_mod_sinus) ->at(1)->at(16)->at(17) ->period(5000);
            manu->mod(new K32_mod_sinus) ->at(2)  ->period(5000) ->phase(120);
            manu->mod(new K32_mod_sinus) ->at(3)  ->period(5000) ->phase(240);
        }
    }


    // PREVIEW Macro
    int previewMacro = k32->remote->getPreviewMacro();
    if ( didChange(W_PREVMACRO, previewMacro) ) 
    {
        LOGF("REMOTE: -> set Preview Macro = %d\n", previewMacro);

        k32->light->anim("preview")->push( MEM_PREV[ previewMacro ], LULU_PREVPIX*4 );  
    }


    // STATE Changed
    remoteState stateR = k32->remote->getState();
    if ( didChange(W_STATE, stateR) ) 
    {
        // AUTO
        if (stateR == REMOTE_AUTO || stateR == REMOTE_AUTO_LOCK)
        {
            k32->light->anim("manu")->stop();
            k32->light->anim("preview")->stop();
            k32->light->anim("artnet")->play();
            LOG("REMOTE: -> Mode AUTO");
        }
        
        // STM
        else if (stateR == REMOTE_MANU_STM || stateR == REMOTE_MANU_STM_LOCK)
        {
            k32->light->anim("artnet")->stop();
            k32->light->anim("preview")->play();
            k32->light->anim("manu")->play();
            LOG("REMOTE: -> Mode STM");
        }

        // MANU
        else if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LOCK || stateR == REMOTE_MANU_LAMP)
        {
            k32->light->anim("preview")->play();
            LOG("REMOTE: -> Mode MANU");
        }

    }


    // GO Active Macro
    if (k32->remote->getSendMacro())
        if (stateR == REMOTE_MANU || stateR == REMOTE_MANU_LOCK || stateR == REMOTE_MANU_LAMP) 
        {
            k32->light->anim("artnet")->stop();
            k32->light->anim("manu")->play();
            LOG("REMOTE: -> MANU -> GO Macro !");
        }


    // LAMP
    int lamp = k32->remote->getLamp();
    if ( didChange(W_LAMP, lamp)) 
    {
        if (lamp >= 0) k32->pwm->setAll(lamp);
        else {
            k32->light->anim("artnet")->push();
            k32->light->anim("manu")->push();
        }
        LOGF("REMOTE: -> getLAMP @%d\n", lamp);
    }


} // void boutons();


#endif