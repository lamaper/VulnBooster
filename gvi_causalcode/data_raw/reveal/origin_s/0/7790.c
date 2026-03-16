static unsigned int do_preload ( const char * fname , struct link_map * main_map , const char * where ) {
 const char * objname ;
 const char * err_str = NULL ;
 struct map_args args ;
 bool malloced ;
 args . str = fname ;
 args . loader = main_map ;
 args . mode = __RTLD_SECURE ;
 unsigned int old_nloaded = GL ( dl_ns ) [ LM_ID_BASE ] . _ns_nloaded ;
 ( void ) _dl_catch_error ( & objname , & err_str , & malloced , map_doit , & args ) ;
 if ( __glibc_unlikely ( err_str != NULL ) ) {
 _dl_error_printf ( "\ ERROR: ld.so: object '%s' from %s cannot be preloaded (%s): ignored.\n" , fname , where , err_str ) ;
 }
 else if ( GL ( dl_ns ) [ LM_ID_BASE ] . _ns_nloaded != old_nloaded ) return 1 ;
 return 0 ;
 }