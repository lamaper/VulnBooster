static void map_doit ( void * a ) {
 struct map_args * args = ( struct map_args * ) a ;
 int type = ( args -> mode == __RTLD_OPENEXEC ) ? lt_executable : lt_library ;
 args -> map = _dl_map_object ( args -> loader , args -> str , type , 0 , args -> mode , LM_ID_BASE ) ;
 }