static int rtp_event_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * rtp_event_info ) {
 const struct _rtp_event_info * pi = ( const struct _rtp_event_info * ) rtp_event_info ;
 if ( pi -> info_setup_frame_num == 0 ) {
 return 0 ;
 }
 rtp_evt_frame_num = pinfo -> fd -> num ;
 rtp_evt = pi -> info_rtp_evt ;
 rtp_evt_end = pi -> info_end ;
 return 0 ;
 }