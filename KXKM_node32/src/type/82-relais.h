
#define L_NAME "Relais"

#define ATOM_RELAY 23


// SETUP
void setup_device() 
{
    // RELAY OUTPUT
    pinMode(ATOM_RELAY, OUTPUT);
    digitalWrite(ATOM_RELAY, HIGH);

    // event/buzz (from mqtt)
    k32->on("btn/atom-on", [](Orderz *order) { digitalWrite(ATOM_RELAY, LOW); });
    k32->on("event/start", [](Orderz *order) { digitalWrite(ATOM_RELAY, LOW); });   // TODO: replace with K32_relay cmd

    // event/stop (from mqtt)
    k32->on("btn/atom-off", [](Orderz *order) { digitalWrite(ATOM_RELAY, HIGH); });
    k32->on("event/stop", [](Orderz *order) { digitalWrite(ATOM_RELAY, HIGH); });  // TODO: replace with K32_relay cmd
}




