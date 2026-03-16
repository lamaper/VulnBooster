void srtp_event_reporter ( srtp_event_data_t * data ) {
 err_report ( err_level_warning , "srtp: in stream 0x%x: " , data -> stream -> ssrc ) ;
 switch ( data -> event ) {
 case event_ssrc_collision : err_report ( err_level_warning , "\tSSRC collision\n" ) ;
 break ;
 case event_key_soft_limit : err_report ( err_level_warning , "\tkey usage soft limit reached\n" ) ;
 break ;
 case event_key_hard_limit : err_report ( err_level_warning , "\tkey usage hard limit reached\n" ) ;
 break ;
 case event_packet_index_limit : err_report ( err_level_warning , "\tpacket index limit reached\n" ) ;
 break ;
 default : err_report ( err_level_warning , "\tunknown event reported to handler\n" ) ;
 }
 }