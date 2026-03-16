static void release_scaled_references ( VP9_COMP * cpi ) {
 VP9_COMMON * cm = & cpi -> common ;
 int i ;
 for ( i = 0 ;
 i < 3 ;
 i ++ ) cm -> frame_bufs [ cpi -> scaled_ref_idx [ i ] ] . ref_count -- ;
 }