static unsigned int ps2_modifier_bit ( QKeyCode key ) {
 switch ( key ) {
 case Q_KEY_CODE_CTRL : return MOD_CTRL_L ;
 case Q_KEY_CODE_CTRL_R : return MOD_CTRL_R ;
 case Q_KEY_CODE_SHIFT : return MOD_SHIFT_L ;
 case Q_KEY_CODE_SHIFT_R : return MOD_SHIFT_R ;
 case Q_KEY_CODE_ALT : return MOD_ALT_L ;
 case Q_KEY_CODE_ALT_R : return MOD_ALT_R ;
 default : return 0 ;
 }
 }