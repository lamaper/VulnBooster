static void Pass2Encode ( VP9_COMP * cpi , size_t * size , uint8_t * dest , unsigned int * frame_flags ) {
 cpi -> allow_encode_breakout = ENCODE_BREAKOUT_ENABLED ;
 encode_frame_to_data_rate ( cpi , size , dest , frame_flags ) ;
 vp9_twopass_postencode_update ( cpi ) ;
 }