static void cyclic_background_refresh ( VP8_COMP * cpi , int Q , int lf_adjustment ) {
 unsigned char * seg_map = cpi -> segmentation_map ;
 signed char feature_data [ MB_LVL_MAX ] [ MAX_MB_SEGMENTS ] ;
 int i ;
 int block_count = cpi -> cyclic_refresh_mode_max_mbs_perframe ;
 int mbs_in_frame = cpi -> common . mb_rows * cpi -> common . mb_cols ;
 cpi -> cyclic_refresh_q = Q / 2 ;
 vpx_memset ( cpi -> segmentation_map , 0 , mbs_in_frame ) ;
 if ( cpi -> common . frame_type != KEY_FRAME ) {
 i = cpi -> cyclic_refresh_mode_index ;
 assert ( i < mbs_in_frame ) ;
 do {
 if ( cpi -> cyclic_refresh_map [ i ] == 0 ) {
 seg_map [ i ] = 1 ;
 block_count -- ;
 }
 else if ( cpi -> cyclic_refresh_map [ i ] < 0 ) cpi -> cyclic_refresh_map [ i ] ++ ;
 i ++ ;
 if ( i == mbs_in_frame ) i = 0 ;
 }
 while ( block_count && i != cpi -> cyclic_refresh_mode_index ) ;
 cpi -> cyclic_refresh_mode_index = i ;

 if ( cpi -> denoiser . denoiser_mode == kDenoiserOnYUVAggressive && Q < ( int ) cpi -> denoiser . denoise_pars . qp_thresh ) {
 cpi -> cyclic_refresh_q = Q ;
 lf_adjustment = - MAX_LOOP_FILTER ;
 for ( i = 0 ;
 i < mbs_in_frame ;
 ++ i ) {
 seg_map [ i ] = ( cpi -> consec_zero_last [ i ] > cpi -> denoiser . denoise_pars . consec_zerolast ) ? 1 : 0 ;
 }
 }
 }

 cpi -> mb . e_mbd . update_mb_segmentation_map = 1 ;
 cpi -> mb . e_mbd . update_mb_segmentation_data = 1 ;
 enable_segmentation ( cpi ) ;
 feature_data [ MB_LVL_ALT_Q ] [ 0 ] = 0 ;
 feature_data [ MB_LVL_ALT_Q ] [ 1 ] = ( cpi -> cyclic_refresh_q - Q ) ;
 feature_data [ MB_LVL_ALT_Q ] [ 2 ] = 0 ;
 feature_data [ MB_LVL_ALT_Q ] [ 3 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 0 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 1 ] = lf_adjustment ;
 feature_data [ MB_LVL_ALT_LF ] [ 2 ] = 0 ;
 feature_data [ MB_LVL_ALT_LF ] [ 3 ] = 0 ;
 set_segment_data ( cpi , & feature_data [ 0 ] [ 0 ] , SEGMENT_DELTADATA ) ;
 }