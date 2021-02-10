#pragma comment ( lib, "wii_wrapper.lib"     )

//This dll is a translator to make the WiimoteLib.dll compatible with dbpro.
// To use this connect your wiimote by pressing the 1 + 2 buttons then searching on your computer. 
//It should appear as 'Nintendo RVL-CNT-01'. 
//Once connected run the demo and your wiimote should rumble with flashing leds. 
//You can also press any of the buttons (except power or 1+2 simultaneously).
//The leds also change with mouse movement and rumble is toggled with mouse movement. 
//Demo now also supports the nunchuck extension.
//IMPORTANT: For this to work WiimoteLib.dll must be in the same folder as your exe!!
//ALSO IMPORTANT: 
//Atm the application will crash if wm connect is attempted before the remote has connected.

//thanks to dale from the dbpro forums for this dll and whoever made the wiimote lib , all i have done is made 
//a wrapper of dales dll to make it compatible with dark gdk , so thanks again dale.



//Below are the values for the function  int wm_setreporttype(int report)

enum input_report{

	BUTTONS = 0,
    BUTTONS_AC = 1,
    BUTTONS_EXTENSION = 2,
	EXTENSION_AC = 3,
	IR_AC = 4,
	IR_EXTENSION_AC = 5 };

/////////get extension values////////////
//# 0 - None
//1 - Partially Inserted
//2 - Nunchuck
//3 - Classic Controller
//4 - Guitar
//5 - Balance Board
//# Returns -1 if an error occured

/////////////////////////////////////////

///////////////IR state///////////////
//0 - Off
//1 - Basic
//2 - Extended
//////////////////////////////////////


int wm_connect();
void wm_disconnect();
int wm_home_pressed();
int wm_up_pressed();
int wm_down_pressed();
int wm_left_pressed();
int wm_right_pressed();
int wm_a_pressed();
int wm_b_pressed();
int wm_one_pressed();
int wm_two_pressed();
int wm_plus_pressed();
int wm_minus_pressed();
int wm_accx_raw();
int wm_accy_raw();
int wm_accz_raw();
int wm_setreporttype(int report);
int wm_accx();
int wm_accy();
int wm_accz();
int wm_enable_rumble(int choice);
int wm_set_rumble(int choice);
int wm_is_rumble_enabled();
int wm_get_battery();
int wm_get_batteryraw();
int wm_set_leds(int l1,int l2,int l3,int l4);
int wm_get_led(int led);
int wm_get_extension();
int wm_guitarblue_pressed();
int wm_guitargreen_pressed();
int wm_guitarred_pressed();
int wm_guitarorange_pressed();
int wm_guitaryellow_pressed();
int wm_guitarminus_pressed();
int wm_guitarplus_pressed();
int wm_guitarstrum_up();
int wm_guitarstrum_down();
float wm_guitarjoystick_x();
float wm_guitarjoystick_y();
int wm_guitarjoystick_rawx();
int wm_guitarjoystick_rawy();
float wm_guitar_whammy();
int wm_whammy_raw();
int wm_getnum_ir();
float wm_getir_x(int ir);
float wm_getir_y(int ir);
int wm_getir_rawx(int ir);
int wm_getir_rawy(int ir);
int wm_setirstate(int state);
int wm_getnunchuckc_pressed();
int wm_getnunchuckz_pressed();
float wm_nunchuckjoystick_x();
float wm_nunchuckjoystick_y();
int wm_nunchuckjoystick_rawx();
int wm_nunchuckjoystick_rawy();
float wm_nunchuckacc_x();
float wm_nunchuckacc_y();
float wm_nunchuckacc_z();
int wm_nunchuckacc_rawx();
int wm_nunchuckacc_rawy();
int wm_nunchuckacc_rawz();


