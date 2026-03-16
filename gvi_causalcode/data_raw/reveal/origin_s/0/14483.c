static void dlmopen_doit ( void * a ) {
 struct dlmopen_args * args = ( struct dlmopen_args * ) a ;
 args -> map = _dl_open ( args -> fname , ( RTLD_LAZY | __RTLD_DLOPEN | __RTLD_AUDIT | __RTLD_SECURE ) , dl_main , LM_ID_NEWLM , _dl_argc , _dl_argv , __environ ) ;
 }