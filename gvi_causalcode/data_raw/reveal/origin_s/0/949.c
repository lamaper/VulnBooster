static void do_vapic_enable ( void * data ) {
 VAPICROMState * s = data ;
 vapic_enable ( s , first_cpu ) ;
 }