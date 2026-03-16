void vp9_loop_filter_init ( VP9_COMMON * cm ) {
 loop_filter_info_n * lfi = & cm -> lf_info ;
 struct loopfilter * lf = & cm -> lf ;
 int lvl ;
 update_sharpness ( lfi , lf -> sharpness_level ) ;
 lf -> last_sharpness_level = lf -> sharpness_level ;
 for ( lvl = 0 ;
 lvl <= MAX_LOOP_FILTER ;
 lvl ++ ) vpx_memset ( lfi -> lfthr [ lvl ] . hev_thr , ( lvl >> 4 ) , SIMD_WIDTH ) ;
 }