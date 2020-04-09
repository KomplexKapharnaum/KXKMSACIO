/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  BOUTONS   ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#ifndef boutons_h
#define boutons_h

#include "mem.h"

int manu_counter = -1;
bool state_btn = false;

void boutons_init() 
{
    if (k32->system->hw() == 3) pinMode(39, INPUT_PULLUP);
}


void boutons_loop()
{
    //////////////////     Click on ESP   ////////////////////
    if (k32->system->stm32->clicked())
    {
        manu_counter = (manu_counter+1) % NUMBER_OF_MEM;

        k32->light->anim("manu")->push( MEM[manu_counter], LULU_PATCHSIZE );
        // k32->light->anim("preview")->push( MEM_PREV[manu_counter], LULU_PREVSIZE );
    }

    //////////////////    Click on Atom    ////////////////////
    if (k32->system->hw() == 3)
    {
        if ((digitalRead(39) >= 1) && (state_btn != false)) state_btn = false;
        else if ((digitalRead(39) <= 0) && (state_btn != true))
        {
        state_btn = true;
        manu_counter = (manu_counter+1) % NUMBER_OF_MEM;

        k32->light->anim("manu")->push( MEM[manu_counter], LULU_PATCHSIZE );
        // k32->light->anim("preview")->push( MEM_PREV[manu_counter], LULU_PREVSIZE );

        }
    }

    //////////////////////  REMOTE CONTROL   ///////////////////////////

    k32->light->anim("remote")->push( k32->remote->getState() );            // remote_status()
    k32->light->anim("preview")->push( k32->remote->getPreviewMacro() );    // preview_frame()

/*                                                                      // !!! IMPLEMENT
    remote_status(k32->remote->getState()); //

    if (k32->remote->getState() > 3)
    {

        // getPreviewMacro()
        gpm = k32->remote->getPreviewMacro();
        if (gpm < 0)
            gpm = 12;
        if (last_gpm != gpm)
        {
            last_gpm = gpm;
            preview_frame(gpm);
        } // getPreviewMacro()

        //  Active FRAME
        gam = k32->remote->getActiveMacro();
        if (k32->remote->getSendMacro() == true || last_gam == gam)
        {
            last_gam = gam;
            active_frame(gam);
            k32->remote->setSendMacro();
        } // Active FRAME

    } // == REMOTE_MANU_LOCK || REMOTE_MANU || REMOTE_MANU_LAMP
    else if (k32->remote->getState() < 2)
    {
        last_gam = -127;
        gpm = NUMBER_OF_MEM - 1;
        if (last_gpm != gpm)
        {
            last_gpm = gpm;
            preview_frame(gpm);
        }
    } // == REMOTE_AUTO || REMOTE_AUTO_LOCK

    if (k32->remote->getState() > 1 && k32->remote->getState() < 4)
    {
        active_frame(gam);
    } // == REMOTE_MANU_STM || REMOTE_MANU_STM_LOCK // rafrechire les modulos si manu btn
    else if (k32->remote->getState() == 4 && k32->remote->getLamp() != old_getlamp)
    {
        old_getlamp = k32->remote->getLamp();
        if (k32->remote->getLamp() >= 0)
        {
            k32->pwm->setAll(k32->remote->getLamp());
        }
        else
        {
            k32->pwm->setAll(0);
        }
    }

    log_get = k32->remote->getState();
    if (log_get != old_log_get)
    {
#ifdef DEBUG_btn
        LOGF(" *  old_STATE = %d\n", old_log_get);
#endif
        if (old_log_get == 0)
        {
            last_gam = -127;
        }
        else if (old_log_get == 6)
        {
            if (k32->remote->getLamp() >= 0)
            {
                k32->pwm->setAll(k32->remote->getLamp());
            }
            else
            {
                k32->pwm->setAll(0);
            }
        }
        if (log_get == 0) // REMOTE_AUTO_LOCK
        {
            k32->remote->setSendMacro();
        }
        else if (log_get == 1) // REMOTE_AUTO
        {
            k32->remote->setSendMacro();
        }
        else if (log_get == 2) // REMOTE_MANU_STM
        {
            k32->remote->setSendMacro();
        }
        else if (log_get == 3) // REMOTE_MANU_STM_LOCK
        {
            k32->remote->setSendMacro();
        }
        else if (log_get == 4) // REMOTE_MANU_LOCK,
        {
        }
        else if (log_get == 5) // REMOTE_MANU
        {
        }
        else if (log_get == 6) // REMOTE_MANU_LAMP
        {
        }

        old_log_get = log_get;
#ifdef DEBUG_btn
        LOGF(" * last_gpm = %d\n", last_gpm);
        LOGF(" * gpm = %d\n", gpm);
        LOGF(" * NEW STATE = %d\n", log_get);
#endif
    } // if (log_get != old_log_get)

    */
} // void boutons();


#endif