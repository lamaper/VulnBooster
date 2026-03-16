void vp9_set_rd_speed_thresholds ( VP9_COMP * cpi ) {
 int i ;
 RD_OPT * const rd = & cpi -> rd ;
 SPEED_FEATURES * const sf = & cpi -> sf ;
 for ( i = 0 ;
 i < MAX_MODES ;
 ++ i ) rd -> thresh_mult [ i ] = cpi -> oxcf . mode == BEST ? - 500 : 0 ;
 rd -> thresh_mult [ THR_NEARESTMV ] = 0 ;
 rd -> thresh_mult [ THR_NEARESTG ] = 0 ;
 rd -> thresh_mult [ THR_NEARESTA ] = 0 ;
 rd -> thresh_mult [ THR_DC ] += 1000 ;
 rd -> thresh_mult [ THR_NEWMV ] += 1000 ;
 rd -> thresh_mult [ THR_NEWA ] += 1000 ;
 rd -> thresh_mult [ THR_NEWG ] += 1000 ;
 rd -> thresh_mult [ THR_NEWMV ] += sf -> elevate_newmv_thresh ;
 rd -> thresh_mult [ THR_NEARMV ] += 1000 ;
 rd -> thresh_mult [ THR_NEARA ] += 1000 ;
 rd -> thresh_mult [ THR_COMP_NEARESTLA ] += 1000 ;
 rd -> thresh_mult [ THR_COMP_NEARESTGA ] += 1000 ;
 rd -> thresh_mult [ THR_TM ] += 1000 ;
 rd -> thresh_mult [ THR_COMP_NEARLA ] += 1500 ;
 rd -> thresh_mult [ THR_COMP_NEWLA ] += 2000 ;
 rd -> thresh_mult [ THR_NEARG ] += 1000 ;
 rd -> thresh_mult [ THR_COMP_NEARGA ] += 1500 ;
 rd -> thresh_mult [ THR_COMP_NEWGA ] += 2000 ;
 rd -> thresh_mult [ THR_ZEROMV ] += 2000 ;
 rd -> thresh_mult [ THR_ZEROG ] += 2000 ;
 rd -> thresh_mult [ THR_ZEROA ] += 2000 ;
 rd -> thresh_mult [ THR_COMP_ZEROLA ] += 2500 ;
 rd -> thresh_mult [ THR_COMP_ZEROGA ] += 2500 ;
 rd -> thresh_mult [ THR_H_PRED ] += 2000 ;
 rd -> thresh_mult [ THR_V_PRED ] += 2000 ;
 rd -> thresh_mult [ THR_D45_PRED ] += 2500 ;
 rd -> thresh_mult [ THR_D135_PRED ] += 2500 ;
 rd -> thresh_mult [ THR_D117_PRED ] += 2500 ;
 rd -> thresh_mult [ THR_D153_PRED ] += 2500 ;
 rd -> thresh_mult [ THR_D207_PRED ] += 2500 ;
 rd -> thresh_mult [ THR_D63_PRED ] += 2500 ;
 if ( ! ( cpi -> ref_frame_flags & VP9_LAST_FLAG ) ) {
 rd -> thresh_mult [ THR_NEWMV ] = INT_MAX ;
 rd -> thresh_mult [ THR_NEARESTMV ] = INT_MAX ;
 rd -> thresh_mult [ THR_ZEROMV ] = INT_MAX ;
 rd -> thresh_mult [ THR_NEARMV ] = INT_MAX ;
 }
 if ( ! ( cpi -> ref_frame_flags & VP9_GOLD_FLAG ) ) {
 rd -> thresh_mult [ THR_NEARESTG ] = INT_MAX ;
 rd -> thresh_mult [ THR_ZEROG ] = INT_MAX ;
 rd -> thresh_mult [ THR_NEARG ] = INT_MAX ;
 rd -> thresh_mult [ THR_NEWG ] = INT_MAX ;
 }
 if ( ! ( cpi -> ref_frame_flags & VP9_ALT_FLAG ) ) {
 rd -> thresh_mult [ THR_NEARESTA ] = INT_MAX ;
 rd -> thresh_mult [ THR_ZEROA ] = INT_MAX ;
 rd -> thresh_mult [ THR_NEARA ] = INT_MAX ;
 rd -> thresh_mult [ THR_NEWA ] = INT_MAX ;
 }
 if ( ( cpi -> ref_frame_flags & ( VP9_LAST_FLAG | VP9_ALT_FLAG ) ) != ( VP9_LAST_FLAG | VP9_ALT_FLAG ) ) {
 rd -> thresh_mult [ THR_COMP_ZEROLA ] = INT_MAX ;
 rd -> thresh_mult [ THR_COMP_NEARESTLA ] = INT_MAX ;
 rd -> thresh_mult [ THR_COMP_NEARLA ] = INT_MAX ;
 rd -> thresh_mult [ THR_COMP_NEWLA ] = INT_MAX ;
 }
 if ( ( cpi -> ref_frame_flags & ( VP9_GOLD_FLAG | VP9_ALT_FLAG ) ) != ( VP9_GOLD_FLAG | VP9_ALT_FLAG ) ) {
 rd -> thresh_mult [ THR_COMP_ZEROGA ] = INT_MAX ;
 rd -> thresh_mult [ THR_COMP_NEARESTGA ] = INT_MAX ;
 rd -> thresh_mult [ THR_COMP_NEARGA ] = INT_MAX ;
 rd -> thresh_mult [ THR_COMP_NEWGA ] = INT_MAX ;
 }
 }