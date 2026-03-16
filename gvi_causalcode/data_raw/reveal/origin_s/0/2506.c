static int com_pager ( String * buffer __attribute__ ( ( unused ) ) , char * line __attribute__ ( ( unused ) ) ) {
 char pager_name [ FN_REFLEN ] , * end , * param ;
 if ( status . batch ) return 0 ;
 while ( my_isspace ( charset_info , * line ) ) line ++ ;
 param = strchr ( line , ' ' ) ;
 while ( param && my_isspace ( charset_info , * param ) ) param ++ ;
 if ( ! param || ! strlen ( param ) ) {
 if ( ! default_pager_set ) {
 tee_fprintf ( stdout , "Default pager wasn't set, using stdout.\n" ) ;
 opt_nopager = 1 ;
 strmov ( pager , "stdout" ) ;
 PAGER = stdout ;
 return 0 ;
 }
 strmov ( pager , default_pager ) ;
 }
 else {
 end = strmake_buf ( pager_name , param ) ;
 while ( end > pager_name && ( my_isspace ( charset_info , end [ - 1 ] ) || my_iscntrl ( charset_info , end [ - 1 ] ) ) ) end -- ;
 end [ 0 ] = 0 ;
 strmov ( pager , pager_name ) ;
 strmov ( default_pager , pager_name ) ;
 }
 opt_nopager = 0 ;
 tee_fprintf ( stdout , "PAGER set to '%s'\n" , pager ) ;
 return 0 ;
 }