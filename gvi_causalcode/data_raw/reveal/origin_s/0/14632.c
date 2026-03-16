static void dealloc_compressor_data ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int i ;
 vpx_free ( cpi -> segmentation_map ) ;
 cpi -> segmentation_map = NULL ;
 vpx_free ( cm -> last_frame_seg_map ) ;
 cm -> last_frame_seg_map = NULL ;
 vpx_free ( cpi -> coding_context . last_frame_seg_map_copy ) ;
 cpi -> coding_context . last_frame_seg_map_copy = NULL ;
 vpx_free ( cpi -> complexity_map ) ;
 cpi -> complexity_map = NULL ;
 vpx_free ( cpi -> nmvcosts [ 0 ] ) ;
 vpx_free ( cpi -> nmvcosts [ 1 ] ) ;
 cpi -> nmvcosts [ 0 ] = NULL ;
 cpi -> nmvcosts [ 1 ] = NULL ;
 vpx_free ( cpi -> nmvcosts_hp [ 0 ] ) ;
 vpx_free ( cpi -> nmvcosts_hp [ 1 ] ) ;
 cpi -> nmvcosts_hp [ 0 ] = NULL ;
 cpi -> nmvcosts_hp [ 1 ] = NULL ;
 vpx_free ( cpi -> nmvsadcosts [ 0 ] ) ;
 vpx_free ( cpi -> nmvsadcosts [ 1 ] ) ;
 cpi -> nmvsadcosts [ 0 ] = NULL ;
 cpi -> nmvsadcosts [ 1 ] = NULL ;
 vpx_free ( cpi -> nmvsadcosts_hp [ 0 ] ) ;
 vpx_free ( cpi -> nmvsadcosts_hp [ 1 ] ) ;
 cpi -> nmvsadcosts_hp [ 0 ] = NULL ;
 cpi -> nmvsadcosts_hp [ 1 ] = NULL ;
 vp9_cyclic_refresh_free ( cpi -> cyclic_refresh ) ;
 cpi -> cyclic_refresh = NULL ;
 vp9_free_ref_frame_buffers ( cm ) ;
 vp9_free_context_buffers ( cm ) ;
 vp9_free_frame_buffer ( & cpi -> last_frame_uf ) ;
 vp9_free_frame_buffer ( & cpi -> scaled_source ) ;
 vp9_free_frame_buffer ( & cpi -> scaled_last_source ) ;
 vp9_free_frame_buffer ( & cpi -> alt_ref_buffer ) ;
 vp9_lookahead_destroy ( cpi -> lookahead ) ;
 vpx_free ( cpi -> tok ) ;
 cpi -> tok = 0 ;
 vp9_free_pc_tree ( cpi ) ;
 for ( i = 0 ;
 i < cpi -> svc . number_spatial_layers ;
 ++ i ) {
 LAYER_CONTEXT * const lc = & cpi -> svc . layer_context [ i ] ;
 vpx_free ( lc -> rc_twopass_stats_in . buf ) ;
 lc -> rc_twopass_stats_in . buf = NULL ;
 lc -> rc_twopass_stats_in . sz = 0 ;
 }
 if ( cpi -> source_diff_var != NULL ) {
 vpx_free ( cpi -> source_diff_var ) ;
 cpi -> source_diff_var = NULL ;
 }
 for ( i = 0 ;
 i < MAX_LAG_BUFFERS ;
 ++ i ) {
 vp9_free_frame_buffer ( & cpi -> svc . scaled_frames [ i ] ) ;
 }
 vpx_memset ( & cpi -> svc . scaled_frames [ 0 ] , 0 , MAX_LAG_BUFFERS * sizeof ( cpi -> svc . scaled_frames [ 0 ] ) ) ;
 }