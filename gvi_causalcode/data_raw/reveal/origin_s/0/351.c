static int process_rec_header2_v145 ( wtap * wth , unsigned char * buffer , guint16 length , gint16 maj_vers , int * err , gchar * * err_info ) {
 if ( length < 5 ) {
 * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup ( "ngsniffer: WAN capture has no network subtype" ) ;
 return - 1 ;
 }
 switch ( buffer [ 4 ] ) {
 case NET_SDLC : wth -> file_encap = WTAP_ENCAP_SDLC ;
 break ;
 case NET_HDLC : wth -> file_encap = WTAP_ENCAP_PER_PACKET ;
 break ;
 case NET_FRAME_RELAY : wth -> file_encap = WTAP_ENCAP_FRELAY_WITH_PHDR ;
 break ;
 case NET_ROUTER : wth -> file_encap = WTAP_ENCAP_PER_PACKET ;
 switch ( maj_vers ) {
 case 4 : if ( buffer [ 1 ] == 0xfa ) wth -> file_encap = WTAP_ENCAP_ISDN ;
 break ;
 case 5 : if ( length < 7 ) {
 * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup ( "ngsniffer: WAN bridge/router capture has no ISDN flag" ) ;
 return - 1 ;
 }
 if ( buffer [ 6 ] == 0x01 ) wth -> file_encap = WTAP_ENCAP_ISDN ;
 break ;
 }
 break ;
 case NET_PPP : wth -> file_encap = WTAP_ENCAP_PPP_WITH_PHDR ;
 break ;
 default : * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup_printf ( "ngsniffer: WAN network subtype %u unknown or unsupported" , buffer [ 4 ] ) ;
 return - 1 ;
 }
 return 0 ;
 }