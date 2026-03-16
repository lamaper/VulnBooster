void ff_h264_init_cabac_states ( H264Context * h ) {
 int i ;
 const int8_t ( * tab ) [ 2 ] ;
 const int slice_qp = av_clip ( h -> qscale - 6 * ( h -> sps . bit_depth_luma - 8 ) , 0 , 51 ) ;
 if ( h -> slice_type_nos == AV_PICTURE_TYPE_I ) tab = cabac_context_init_I ;
 else tab = cabac_context_init_PB [ h -> cabac_init_idc ] ;
 for ( i = 0 ;
 i < 1024 ;
 i ++ ) {
 int pre = 2 * ( ( ( tab [ i ] [ 0 ] * slice_qp ) >> 4 ) + tab [ i ] [ 1 ] ) - 127 ;
 pre ^= pre >> 31 ;
 if ( pre > 124 ) pre = 124 + ( pre & 1 ) ;
 h -> cabac_state [ i ] = pre ;
 }
 }