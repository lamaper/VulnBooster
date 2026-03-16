int vp8_set_roimap ( VP8_COMP * cpi , unsigned char * map , unsigned int rows , unsigned int cols , int delta_q [ 4 ] , int delta_lf [ 4 ] , unsigned int threshold [ 4 ] ) {
 signed char feature_data [ MB_LVL_MAX ] [ MAX_MB_SEGMENTS ] ;
 int internal_delta_q [ MAX_MB_SEGMENTS ] ;
 const int range = 63 ;
 int i ;
 if ( cpi -> cyclic_refresh_mode_enabled ) return - 1 ;
 if ( cpi -> common . mb_rows != rows || cpi -> common . mb_cols != cols ) return - 1 ;
 if ( ( abs ( delta_q [ 0 ] ) > range ) || ( abs ( delta_q [ 1 ] ) > range ) || ( abs ( delta_q [ 2 ] ) > range ) || ( abs ( delta_q [ 3 ] ) > range ) ) return - 1 ;
 if ( ( abs ( delta_lf [ 0 ] ) > range ) || ( abs ( delta_lf [ 1 ] ) > range ) || ( abs ( delta_lf [ 2 ] ) > range ) || ( abs ( delta_lf [ 3 ] ) > range ) ) return - 1 ;
 if ( ! map ) {
 disable_segmentation ( cpi ) ;
 return 0 ;
 }
 for ( i = 0 ;
 i < MAX_MB_SEGMENTS ;
 i ++ ) internal_delta_q [ i ] = ( delta_q [ i ] >= 0 ) ? q_trans [ delta_q [ i ] ] : - q_trans [ - delta_q [ i ] ] ;
 set_segmentation_map ( cpi , map ) ;
 enable_segmentation ( cpi ) ;
 feature_data [ MB_LVL_ALT_Q ] [ 0 ] = internal_delta_q [ 0 ] ;
 feature_data [ MB_LVL_ALT_Q ] [ 1 ] = internal_delta_q [ 1 ] ;
 feature_data [ MB_LVL_ALT_Q ] [ 2 ] = internal_delta_q [ 2 ] ;
 feature_data [ MB_LVL_ALT_Q ] [ 3 ] = internal_delta_q [ 3 ] ;
 feature_data [ MB_LVL_ALT_LF ] [ 0 ] = delta_lf [ 0 ] ;
 feature_data [ MB_LVL_ALT_LF ] [ 1 ] = delta_lf [ 1 ] ;
 feature_data [ MB_LVL_ALT_LF ] [ 2 ] = delta_lf [ 2 ] ;
 feature_data [ MB_LVL_ALT_LF ] [ 3 ] = delta_lf [ 3 ] ;
 cpi -> segment_encode_breakout [ 0 ] = threshold [ 0 ] ;
 cpi -> segment_encode_breakout [ 1 ] = threshold [ 1 ] ;
 cpi -> segment_encode_breakout [ 2 ] = threshold [ 2 ] ;
 cpi -> segment_encode_breakout [ 3 ] = threshold [ 3 ] ;
 set_segment_data ( cpi , & feature_data [ 0 ] [ 0 ] , SEGMENT_DELTADATA ) ;
 return 0 ;
 }