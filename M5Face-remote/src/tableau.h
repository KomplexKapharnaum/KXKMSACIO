#ifndef tableau_h
#define tableau_h

#define max_clients 10
int clients = -1;

String T_ID[max_clients];  // id
String T_CHA[max_clients]; // channel
String T_VER[max_clients]; // version
String T_MAC[max_clients]; // mac adress
String T_IP[max_clients];  // ip
String T_WIF[max_clients]; // wifi rssi
String T_CON[max_clients]; // ?????????
String T_BAT[max_clients]; // battery
String T_FAL[max_clients]; // ?????????
String T_RUN[max_clients]; // playeur state
String T_END[max_clients]; // message end , utile ?

unsigned long T_inlife[max_clients][3]; // 0 id_beat 1 last_time 2 bool inlife

unsigned long currentTime = 0;
unsigned long previousTime = 0;

#endif