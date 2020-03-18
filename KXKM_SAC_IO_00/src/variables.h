///////////////////////////////////dmx variables////////////////////////////////////

float zo_pi_n_1_r[LEDS_ABSOLUTE_MAX];
float zo_pi_n_1_g[LEDS_ABSOLUTE_MAX];
float zo_pi_n_1_b[LEDS_ABSOLUTE_MAX];
float zo_pi_n_1_w[LEDS_ABSOLUTE_MAX];

float pi_n_1_r[LEDS_ABSOLUTE_MAX];
float pi_n_1_g[LEDS_ABSOLUTE_MAX];
float pi_n_1_b[LEDS_ABSOLUTE_MAX];
float pi_n_1_w[LEDS_ABSOLUTE_MAX];

float pi_1_r[LEDS_ABSOLUTE_MAX];
float pi_1_g[LEDS_ABSOLUTE_MAX];
float pi_1_b[LEDS_ABSOLUTE_MAX];
float pi_1_w[LEDS_ABSOLUTE_MAX];

float pi_1_sr[LEDS_ABSOLUTE_MAX];
float pi_1_sg[LEDS_ABSOLUTE_MAX];
float pi_1_sb[LEDS_ABSOLUTE_MAX];
float pi_1_sw[LEDS_ABSOLUTE_MAX];

int color_mode;
int mirror;
int zoom;
int offset;
int di;

unsigned long now;
int effet_etat = 0;
int last_time_effet = 0;
int type_effet = 0;
int modulo = 0;
unsigned int str_ws = 0;
int type_modulo = 0;
int str = 0;
int pix_pos;
int pix_pos_v;
int pix_start;
int pix_center;
int pix_end;
int master;
float rrr;
float ggg;
float bbb;
float www;
float rr;
float gg;
float bb;
float ww;
float r;
float g;
float b;
float w;
float srr;
float sgg;
float sbb;
float sww;
int mod;
int pix_mod;
unsigned long str_ws_last = 0;
#define STROB_ON_MS 15
int pix_start_v;
int ref_pix_pos;
float pix_coef;
float pix_coefi;
float pix_coef_fond;
float pix_coefi_fond;
int S_seuil;
int old_S_seuil = 0;
int a;
float str_blind_ws = 1;

////////////////////////////////// btn variables////////////////////////////////////

int manu_counter = 0;
int state_btn_atom = 0;
int mem_call = -1;

///////////////////////////////////// batterie variable /////////////////////////////////////

int percentage;
int led_niv = 25;
int etat_r = 0;

///////////////////////////////////// Wifi variable /////////////////////////////////////

bool lostConnection = true;
