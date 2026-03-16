static int check_dual_ref_flags ( VP9_COMP * cpi ) {
 const int ref_flags = cpi -> ref_frame_flags ;
 if ( vp9_segfeature_active ( & cpi -> common . seg , 1 , SEG_LVL_REF_FRAME ) ) {
 return 0 ;
 }
 else {
 return ( ! ! ( ref_flags & VP9_GOLD_FLAG ) + ! ! ( ref_flags & VP9_LAST_FLAG ) + ! ! ( ref_flags & VP9_ALT_FLAG ) ) >= 2 ;
 }
 }