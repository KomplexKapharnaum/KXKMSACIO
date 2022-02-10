
#define L_NAME "Buzzer"

#define ARTNET_ENABLE 0

void setup_device() 
{
    
    k32->on("atom/btn-click", [](Orderz* order){

        mqtt->publish("k32/event/buzz", "yo");
        
    });

}




