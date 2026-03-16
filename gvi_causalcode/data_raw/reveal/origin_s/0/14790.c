static void init_h245_packet_info ( h245_packet_info * pi ) {
 if ( pi == NULL ) {
 return ;
 }
 pi -> msg_type = H245_OTHER ;
 pi -> frame_label [ 0 ] = '\0' ;
 g_snprintf ( pi -> comment , sizeof ( pi -> comment ) , "H245 " ) ;
 }