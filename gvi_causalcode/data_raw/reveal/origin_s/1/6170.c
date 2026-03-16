void vp9_set_rd_speed_thresholds_sub8x8 ( VP9_COMP * cpi ) {
 const SPEED_FEATURES * const sf = & cpi -> sf ;
 RD_OPT * const rd = & cpi -> rd ;
 int i ;
 for ( i = 0 ;
 i < MAX_REFS ;
 ++ i ) rd -> thresh_mult_sub8x8 [ i ] = cpi -> oxcf . mode == BEST ? - 500 : 0 ;
 rd -> thresh_mult_sub8x8 [ THR_LAST ] += 2500 ;
 rd -> thresh_mult_sub8x8 [ THR_GOLD ] += 2500 ;
 rd -> thresh_mult_sub8x8 [ THR_ALTR ] += 2500 ;
 rd -> thresh_mult_sub8x8 [ THR_INTRA ] += 2500 ;
 rd -> thresh_mult_sub8x8 [ THR_COMP_LA ] += 4500 ;
 rd -> thresh_mult_sub8x8 [ THR_COMP_GA ] += 4500 ;
 for ( i = 0 ;
 i < MAX_REFS ;
 ++ i ) if ( sf -> disable_split_mask & ( 1 << i ) ) rd -> thresh_mult_sub8x8 [ i ] = INT_MAX ;
 if ( ! ( cpi -> ref_frame_flags & VP9_LAST_FLAG ) ) rd -> thresh_mult_sub8x8 [ THR_LAST ] = INT_MAX ;
 if ( ! ( cpi -> ref_frame_flags & VP9_GOLD_FLAG ) ) rd -> thresh_mult_sub8x8 [ THR_GOLD ] = INT_MAX ;
 if ( ! ( cpi -> ref_frame_flags & VP9_ALT_FLAG ) ) rd -> thresh_mult_sub8x8 [ THR_ALTR ] = INT_MAX ;
 if ( ( cpi -> ref_frame_flags & ( VP9_LAST_FLAG | VP9_ALT_FLAG ) ) != ( VP9_LAST_FLAG | VP9_ALT_FLAG ) ) rd -> thresh_mult_sub8x8 [ THR_COMP_LA ] = INT_MAX ;
 if ( ( cpi -> ref_frame_flags & ( VP9_GOLD_FLAG | VP9_ALT_FLAG ) ) != ( VP9_GOLD_FLAG | VP9_ALT_FLAG ) ) rd -> thresh_mult_sub8x8 [ THR_COMP_GA ] = INT_MAX ;
 }