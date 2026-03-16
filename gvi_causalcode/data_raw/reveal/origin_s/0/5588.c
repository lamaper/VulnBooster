static int arm_cpu_env_flags ( int * flags ) {
 char * env ;
 env = getenv ( "VPX_SIMD_CAPS" ) ;
 if ( env && * env ) {
 * flags = ( int ) strtol ( env , NULL , 0 ) ;
 return 0 ;
 }
 * flags = 0 ;
 return - 1 ;
 }