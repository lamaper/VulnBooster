static int arm_cpu_env_mask ( void ) {
 char * env ;
 env = getenv ( "VPX_SIMD_CAPS_MASK" ) ;
 return env && * env ? ( int ) strtol ( env , NULL , 0 ) : ~ 0 ;
 }