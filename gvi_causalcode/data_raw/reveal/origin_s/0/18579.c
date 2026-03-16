void vp9_update_mbgraph_stats ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int i , n_frames = vp9_lookahead_depth ( cpi -> lookahead ) ;
 YV12_BUFFER_CONFIG * golden_ref = get_ref_frame_buffer ( cpi , GOLDEN_FRAME ) ;
 if ( n_frames <= cpi -> rc . frames_till_gf_update_due ) return ;
 if ( n_frames > MAX_LAG_BUFFERS ) n_frames = MAX_LAG_BUFFERS ;
 cpi -> mbgraph_n_frames = n_frames ;
 for ( i = 0 ;
 i < n_frames ;
 i ++ ) {
 MBGRAPH_FRAME_STATS * frame_stats = & cpi -> mbgraph_stats [ i ] ;
 vpx_memset ( frame_stats -> mb_stats , 0 , cm -> mb_rows * cm -> mb_cols * sizeof ( * cpi -> mbgraph_stats [ i ] . mb_stats ) ) ;
 }
 for ( i = 0 ;
 i < n_frames ;
 i ++ ) {
 MBGRAPH_FRAME_STATS * frame_stats = & cpi -> mbgraph_stats [ i ] ;
 struct lookahead_entry * q_cur = vp9_lookahead_peek ( cpi -> lookahead , i ) ;
 assert ( q_cur != NULL ) ;
 update_mbgraph_frame_stats ( cpi , frame_stats , & q_cur -> img , golden_ref , cpi -> Source ) ;
 }
 vp9_clear_system_state ( ) ;
 separate_arf_mbs ( cpi ) ;
 }