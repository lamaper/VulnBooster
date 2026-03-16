static h225_packet_info * create_h225_packet_info ( packet_info * pinfo ) {
 h225_packet_info * pi = wmem_new0 ( pinfo -> pool , h225_packet_info ) ;
 pi -> msg_type = H225_OTHERS ;
 pi -> cs_type = H225_OTHER ;
 pi -> msg_tag = - 1 ;
 pi -> reason = - 1 ;
 return pi ;
 }