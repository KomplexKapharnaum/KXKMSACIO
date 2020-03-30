/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  BOUTONS   ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void boutons()
{
    //////////////////     Click on ESP   ////////////////////
    if (k32->system->hw() <= 2)
    {
        if (k32->system->stm32->clicked())
        {
            // k32->remote->setManu_Stm();

            if (state_btn == false || k32->remote->getState() > 1)
            {
                state_btn = true;
                k32->remote->setManu_Stm();
            }
            active_frame(++manu_counter);
            preview_frame(manu_counter);
            gam = manu_counter;
        } // Click on ESP
    }

    //////////////////    Click on Atom    ////////////////////
    else if (k32->system->hw() == 3)
    {
        if ((digitalRead(39) >= 1) && (state_btn != false))
        {
            state_btn = false;
        }
        if ((digitalRead(39) <= 0) && (state_btn != true))
        {
            state_btn = true;
            k32->remote->setManu_Stm();
            active_frame(++manu_counter);
            preview_frame(manu_counter);
            gam = manu_counter;
        }
    }

    //////////////////////  REMOTE CONTROL   ///////////////////////////

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
} // void boutons();
