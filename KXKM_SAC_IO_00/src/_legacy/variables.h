///////////////////////////////////dmx variables////////////////////////////////////

int color_mode;
int mirror;
float zoom;
float offset;
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
float rrr, ggg, bbb, www;
float rr, gg, bb, ww;
float r, g, b, w;
float srr, sgg, sbb, sww;
int start_color, end_color;
int mod;
int pix_mod;
unsigned long str_ws_last = 0;
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

int ligne_mod, ligne, pos_ligne;
 uint8_t start_Pixels;

////////////////////////////////// btn variables////////////////////////////////////


bool state_btn = false;
int mem_call = -1;
int gpm;
int last_gpm;
int last_gam = -10;
int gam = 0;
int log_get = -1;
int old_log_get = -129;
int old_getlamp = -129;
int old_ci;

///////////////////////////////////// Wifi variable /////////////////////////////////////

bool lostConnection = true;

///////////////////////////////////// tri & quadri color  variable /////////////////////////////////////

int tri1r, tri1g, tri1b, tri1w;
int tri2r, tri2g, tri2b, tri2w;
int tri3r, tri3g, tri3b, tri3w;
int tri4r, tri4g, tri4b, tri4w;
int rap_tri;
