static void init_pager ( ) {

 if ( ! ( PAGER = popen ( pager , "w" ) ) ) {
 tee_fprintf ( stdout , "popen() failed! defaulting PAGER to stdout!\n" ) ;
 PAGER = stdout ;
 }
 }
 else # endif PAGER = stdout ;
 }