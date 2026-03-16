void vp9_set_rd_speed_thresholds ( VP9_COMP * cpi ) {
 int i ;
 RD_OPT * const rd = & cpi -> rd ;
 SPEED_FEATURES * const sf = & cpi -> sf ;
 for ( i = 0 ;
 i < MAX_MODES ;
 ++ i ) rd -> thresh_mult [ i ] = cpi -> oxcf . mode == BEST ? - 500 : 0 ;
 if ( sf -> adaptive_rd_thresh ) {
 rd -> thresh_mult [ THR_NEARESTMV ] = 300 ;
 rd -> thresh_mult [ THR_NEARESTG ] = 300 ;
 rd -> thresh_mult [ THR_NEARESTA ] = 300 ;
 }
 else {
 rd -> thresh_mult [ THR_NEARESTMV ] = 0 ;
 rd -> thresh_mult [ THR_NEARESTG ] = 0 ;
 rd -> thresh_mult [ THR_NEARESTA ] = 0 ;
 }
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
 }