static bool bind_to_interface ( int sd ) {
 char * iface ;

 int status ;

 return true ;
 }

 strncpy ( ifr . ifr_ifrn . ifrn_name , iface , IFNAMSIZ ) ;
 ifr . ifr_ifrn . ifrn_name [ IFNAMSIZ - 1 ] = 0 ;
 free ( iface ) ;
 status = setsockopt ( sd , SOL_SOCKET , SO_BINDTODEVICE , ( void * ) & ifr , sizeof ( ifr ) ) ;
 if ( status ) {
 logger ( LOG_ERR , "Can't bind to interface %s: %s" , ifr . ifr_ifrn . ifrn_name , strerror ( errno ) ) ;
 return false ;
 }


 }