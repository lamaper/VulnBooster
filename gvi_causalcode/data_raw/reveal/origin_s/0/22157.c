void vp9_init_dsmotion_compensation ( search_site_config * cfg , int stride ) {
 int len , ss_count = 1 ;
 cfg -> ss [ 0 ] . mv . col = cfg -> ss [ 0 ] . mv . row = 0 ;
 cfg -> ss [ 0 ] . offset = 0 ;
 for ( len = MAX_FIRST_STEP ;
 len > 0 ;
 len /= 2 ) {
 const MV ss_mvs [ ] = {
 {
 - len , 0 }
 , {
 len , 0 }
 , {
 0 , - len }
 , {
 0 , len }
 }
 ;
 int i ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 search_site * const ss = & cfg -> ss [ ss_count ++ ] ;
 ss -> mv = ss_mvs [ i ] ;
 ss -> offset = ss -> mv . row * stride + ss -> mv . col ;
 }
 }
 cfg -> ss_count = ss_count ;
 cfg -> searches_per_step = 4 ;
 }