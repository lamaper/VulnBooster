static int get_errno ( void ) {

 XPR ( NT "you found a bug: expected errno != 0\n" ) ;
 errno = XD3_INTERNAL ;
 }
 return errno ;

 if ( err_num == NO_ERROR ) {
 err_num = XD3_INTERNAL ;
 }
 return err_num ;
