void rfbSetProtocolVersion ( rfbScreenInfoPtr rfbScreen , int major_ , int minor_ ) {
 if ( ( major_ == 3 ) && ( minor_ > 2 && minor_ < 9 ) ) {
 rfbScreen -> protocolMajorVersion = major_ ;
 rfbScreen -> protocolMinorVersion = minor_ ;
 }
 else rfbLog ( "rfbSetProtocolVersion(%d,%d) set to invalid values\n" , major_ , minor_ ) ;
 }