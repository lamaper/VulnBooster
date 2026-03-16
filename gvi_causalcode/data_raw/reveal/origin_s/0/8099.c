static int process_rec_header2_v2 ( wtap * wth , unsigned char * buffer , guint16 length , int * err , gchar * * err_info ) {
 static const char x_25_str [ ] = "HDLC\nX.25\n" ;
 if ( length < sizeof x_25_str - 1 ) {
 * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup_printf ( "ngsniffer: WAN capture has too-short protocol list" ) ;
 return - 1 ;
 }
 if ( strncmp ( ( char * ) buffer , x_25_str , sizeof x_25_str - 1 ) == 0 ) {
 wth -> file_encap = WTAP_ENCAP_LAPB ;
 }
 else {
 * err = WTAP_ERR_UNSUPPORTED ;
 * err_info = g_strdup_printf ( "ngsniffer: WAN capture protocol string %.*s unknown" , length , buffer ) ;
 return - 1 ;
 }
 return 0 ;
 }