static void formant_postfilter ( G723_1_Context * p , int16_t * lpc , int16_t * buf , int16_t * dst ) {
 int16_t filter_coef [ 2 ] [ LPC_ORDER ] ;
 int filter_signal [ LPC_ORDER + FRAME_LEN ] , * signal_ptr ;
 int i , j , k ;
 memcpy ( buf , p -> fir_mem , LPC_ORDER * sizeof ( * buf ) ) ;
 memcpy ( filter_signal , p -> iir_mem , LPC_ORDER * sizeof ( * filter_signal ) ) ;
 for ( i = LPC_ORDER , j = 0 ;
 j < SUBFRAMES ;
 i += SUBFRAME_LEN , j ++ ) {
 for ( k = 0 ;
 k < LPC_ORDER ;
 k ++ ) {
 filter_coef [ 0 ] [ k ] = ( - lpc [ k ] * postfilter_tbl [ 0 ] [ k ] + ( 1 << 14 ) ) >> 15 ;
 filter_coef [ 1 ] [ k ] = ( - lpc [ k ] * postfilter_tbl [ 1 ] [ k ] + ( 1 << 14 ) ) >> 15 ;
 }
 iir_filter ( filter_coef [ 0 ] , filter_coef [ 1 ] , buf + i , filter_signal + i ) ;
 lpc += LPC_ORDER ;
 }
 memcpy ( p -> fir_mem , buf + FRAME_LEN , LPC_ORDER * sizeof ( * p -> fir_mem ) ) ;
 memcpy ( p -> iir_mem , filter_signal + FRAME_LEN , LPC_ORDER * sizeof ( * p -> iir_mem ) ) ;
 buf += LPC_ORDER ;
 signal_ptr = filter_signal + LPC_ORDER ;
 for ( i = 0 ;
 i < SUBFRAMES ;
 i ++ ) {
 int temp ;
 int auto_corr [ 2 ] ;
 int scale , energy ;
 scale = scale_vector ( dst , buf , SUBFRAME_LEN ) ;
 auto_corr [ 0 ] = dot_product ( dst , dst + 1 , SUBFRAME_LEN - 1 ) ;
 auto_corr [ 1 ] = dot_product ( dst , dst , SUBFRAME_LEN ) ;
 temp = auto_corr [ 1 ] >> 16 ;
 if ( temp ) {
 temp = ( auto_corr [ 0 ] >> 2 ) / temp ;
 }
 p -> reflection_coef = ( 3 * p -> reflection_coef + temp + 2 ) >> 2 ;
 temp = - p -> reflection_coef >> 1 & ~ 3 ;
 for ( j = 0 ;
 j < SUBFRAME_LEN ;
 j ++ ) {
 dst [ j ] = av_sat_dadd32 ( signal_ptr [ j ] , ( signal_ptr [ j - 1 ] >> 16 ) * temp ) >> 16 ;
 }
 temp = 2 * scale + 4 ;
 if ( temp < 0 ) {
 energy = av_clipl_int32 ( ( int64_t ) auto_corr [ 1 ] << - temp ) ;
 }
 else energy = auto_corr [ 1 ] >> temp ;
 gain_scale ( p , dst , energy ) ;
 buf += SUBFRAME_LEN ;
 signal_ptr += SUBFRAME_LEN ;
 dst += SUBFRAME_LEN ;
 }
 }