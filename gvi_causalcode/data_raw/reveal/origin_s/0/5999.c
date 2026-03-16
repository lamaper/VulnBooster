static void version_check_doit ( void * a ) {
 struct version_check_args * args = ( struct version_check_args * ) a ;
 if ( _dl_check_all_versions ( GL ( dl_ns ) [ LM_ID_BASE ] . _ns_loaded , 1 , args -> dotrace ) && args -> doexit ) _exit ( 1 ) ;
 }