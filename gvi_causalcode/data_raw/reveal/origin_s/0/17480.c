static int unpack_bitstream ( G723_1_Context * p , const uint8_t * buf , int buf_size ) {
 GetBitContext gb ;
 int ad_cb_len ;
 int temp , info_bits , i ;
 init_get_bits ( & gb , buf , buf_size * 8 ) ;
 info_bits = get_bits ( & gb , 2 ) ;
 if ( info_bits == 3 ) {
 p -> cur_frame_type = UNTRANSMITTED_FRAME ;
 return 0 ;
 }
 p -> lsp_index [ 2 ] = get_bits ( & gb , 8 ) ;
 p -> lsp_index [ 1 ] = get_bits ( & gb , 8 ) ;
 p -> lsp_index [ 0 ] = get_bits ( & gb , 8 ) ;
 if ( info_bits == 2 ) {
 p -> cur_frame_type = SID_FRAME ;
 p -> subframe [ 0 ] . amp_index = get_bits ( & gb , 6 ) ;
 return 0 ;
 }
 p -> cur_rate = info_bits ? RATE_5300 : RATE_6300 ;
 p -> cur_frame_type = ACTIVE_FRAME ;
 p -> pitch_lag [ 0 ] = get_bits ( & gb , 7 ) ;
 if ( p -> pitch_lag [ 0 ] > 123 ) return - 1 ;
 p -> pitch_lag [ 0 ] += PITCH_MIN ;
 p -> subframe [ 1 ] . ad_cb_lag = get_bits ( & gb , 2 ) ;
 p -> pitch_lag [ 1 ] = get_bits ( & gb , 7 ) ;
 if ( p -> pitch_lag [ 1 ] > 123 ) return - 1 ;
 p -> pitch_lag [ 1 ] += PITCH_MIN ;
 p -> subframe [ 3 ] . ad_cb_lag = get_bits ( & gb , 2 ) ;
 p -> subframe [ 0 ] . ad_cb_lag = 1 ;
 p -> subframe [ 2 ] . ad_cb_lag = 1 ;
 for ( i = 0 ;
 i < SUBFRAMES ;
 i ++ ) {
 temp = get_bits ( & gb , 12 ) ;
 ad_cb_len = 170 ;
 p -> subframe [ i ] . dirac_train = 0 ;
 if ( p -> cur_rate == RATE_6300 && p -> pitch_lag [ i >> 1 ] < SUBFRAME_LEN - 2 ) {
 p -> subframe [ i ] . dirac_train = temp >> 11 ;
 temp &= 0x7FF ;
 ad_cb_len = 85 ;
 }
 p -> subframe [ i ] . ad_cb_gain = FASTDIV ( temp , GAIN_LEVELS ) ;
 if ( p -> subframe [ i ] . ad_cb_gain < ad_cb_len ) {
 p -> subframe [ i ] . amp_index = temp - p -> subframe [ i ] . ad_cb_gain * GAIN_LEVELS ;
 }
 else {
 return - 1 ;
 }
 }
 p -> subframe [ 0 ] . grid_index = get_bits ( & gb , 1 ) ;
 p -> subframe [ 1 ] . grid_index = get_bits ( & gb , 1 ) ;
 p -> subframe [ 2 ] . grid_index = get_bits ( & gb , 1 ) ;
 p -> subframe [ 3 ] . grid_index = get_bits ( & gb , 1 ) ;
 if ( p -> cur_rate == RATE_6300 ) {
 skip_bits ( & gb , 1 ) ;
 temp = get_bits ( & gb , 13 ) ;
 p -> subframe [ 0 ] . pulse_pos = temp / 810 ;
 temp -= p -> subframe [ 0 ] . pulse_pos * 810 ;
 p -> subframe [ 1 ] . pulse_pos = FASTDIV ( temp , 90 ) ;
 temp -= p -> subframe [ 1 ] . pulse_pos * 90 ;
 p -> subframe [ 2 ] . pulse_pos = FASTDIV ( temp , 9 ) ;
 p -> subframe [ 3 ] . pulse_pos = temp - p -> subframe [ 2 ] . pulse_pos * 9 ;
 p -> subframe [ 0 ] . pulse_pos = ( p -> subframe [ 0 ] . pulse_pos << 16 ) + get_bits ( & gb , 16 ) ;
 p -> subframe [ 1 ] . pulse_pos = ( p -> subframe [ 1 ] . pulse_pos << 14 ) + get_bits ( & gb , 14 ) ;
 p -> subframe [ 2 ] . pulse_pos = ( p -> subframe [ 2 ] . pulse_pos << 16 ) + get_bits ( & gb , 16 ) ;
 p -> subframe [ 3 ] . pulse_pos = ( p -> subframe [ 3 ] . pulse_pos << 14 ) + get_bits ( & gb , 14 ) ;
 p -> subframe [ 0 ] . pulse_sign = get_bits ( & gb , 6 ) ;
 p -> subframe [ 1 ] . pulse_sign = get_bits ( & gb , 5 ) ;
 p -> subframe [ 2 ] . pulse_sign = get_bits ( & gb , 6 ) ;
 p -> subframe [ 3 ] . pulse_sign = get_bits ( & gb , 5 ) ;
 }
 else {
 p -> subframe [ 0 ] . pulse_pos = get_bits ( & gb , 12 ) ;
 p -> subframe [ 1 ] . pulse_pos = get_bits ( & gb , 12 ) ;
 p -> subframe [ 2 ] . pulse_pos = get_bits ( & gb , 12 ) ;
 p -> subframe [ 3 ] . pulse_pos = get_bits ( & gb , 12 ) ;
 p -> subframe [ 0 ] . pulse_sign = get_bits ( & gb , 4 ) ;
 p -> subframe [ 1 ] . pulse_sign = get_bits ( & gb , 4 ) ;
 p -> subframe [ 2 ] . pulse_sign = get_bits ( & gb , 4 ) ;
 p -> subframe [ 3 ] . pulse_sign = get_bits ( & gb , 4 ) ;
 }
 return 0 ;
 }