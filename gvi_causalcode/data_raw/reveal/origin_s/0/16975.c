static void rfbProcessClientProtocolVersion ( rfbClientPtr cl ) {
 rfbProtocolVersionMsg pv ;
 int n , major_ , minor_ ;
 if ( ( n = rfbReadExact ( cl , pv , sz_rfbProtocolVersionMsg ) ) <= 0 ) {
 if ( n == 0 ) rfbLog ( "rfbProcessClientProtocolVersion: client gone\n" ) ;
 else rfbLogPerror ( "rfbProcessClientProtocolVersion: read" ) ;
 rfbCloseClient ( cl ) ;
 return ;
 }
 pv [ sz_rfbProtocolVersionMsg ] = 0 ;
 if ( sscanf ( pv , rfbProtocolVersionFormat , & major_ , & minor_ ) != 2 ) {
 rfbErr ( "rfbProcessClientProtocolVersion: not a valid RFB client: %s\n" , pv ) ;
 rfbCloseClient ( cl ) ;
 return ;
 }
 rfbLog ( "Client Protocol Version %d.%d\n" , major_ , minor_ ) ;
 if ( major_ != rfbProtocolMajorVersion ) {
 rfbErr ( "RFB protocol version mismatch - server %d.%d, client %d.%d" , cl -> screen -> protocolMajorVersion , cl -> screen -> protocolMinorVersion , major_ , minor_ ) ;
 rfbCloseClient ( cl ) ;
 return ;
 }
 cl -> protocolMajorVersion = major_ ;
 cl -> protocolMinorVersion = minor_ ;
 rfbLog ( "Protocol version sent %d.%d, using %d.%d\n" , major_ , minor_ , rfbProtocolMajorVersion , cl -> protocolMinorVersion ) ;
 rfbAuthNewClient ( cl ) ;
 }