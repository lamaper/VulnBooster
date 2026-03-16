static void set_root ( const char * path ) {

 sql_perror ( "chroot" ) ;
 unireg_abort ( 1 ) ;
 }
 my_setwd ( "/" , MYF ( 0 ) ) ;
