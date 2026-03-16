void vp9_loop_filter_frame_init ( VP9_COMMON * cm , int default_filt_lvl ) {
 int seg_id ;
 const int scale = 1 << ( default_filt_lvl >> 5 ) ;
 loop_filter_info_n * const lfi = & cm -> lf_info ;
 struct loopfilter * const lf = & cm -> lf ;
 const struct segmentation * const seg = & cm -> seg ;
 if ( lf -> last_sharpness_level != lf -> sharpness_level ) {
 update_sharpness ( lfi , lf -> sharpness_level ) ;
 lf -> last_sharpness_level = lf -> sharpness_level ;
 }
 for ( seg_id = 0 ;
 seg_id < MAX_SEGMENTS ;
 seg_id ++ ) {
 int lvl_seg = default_filt_lvl ;
 if ( vp9_segfeature_active ( seg , seg_id , SEG_LVL_ALT_LF ) ) {
 const int data = vp9_get_segdata ( seg , seg_id , SEG_LVL_ALT_LF ) ;
 lvl_seg = clamp ( seg -> abs_delta == SEGMENT_ABSDATA ? data : default_filt_lvl + data , 0 , MAX_LOOP_FILTER ) ;
 }
 if ( ! lf -> mode_ref_delta_enabled ) {
 vpx_memset ( lfi -> lvl [ seg_id ] , lvl_seg , sizeof ( lfi -> lvl [ seg_id ] ) ) ;
 }
 else {
 int ref , mode ;
 const int intra_lvl = lvl_seg + lf -> ref_deltas [ INTRA_FRAME ] * scale ;
 lfi -> lvl [ seg_id ] [ INTRA_FRAME ] [ 0 ] = clamp ( intra_lvl , 0 , MAX_LOOP_FILTER ) ;
 for ( ref = LAST_FRAME ;
 ref < MAX_REF_FRAMES ;
 ++ ref ) {
 for ( mode = 0 ;
 mode < MAX_MODE_LF_DELTAS ;
 ++ mode ) {
 const int inter_lvl = lvl_seg + lf -> ref_deltas [ ref ] * scale + lf -> mode_deltas [ mode ] * scale ;
 lfi -> lvl [ seg_id ] [ ref ] [ mode ] = clamp ( inter_lvl , 0 , MAX_LOOP_FILTER ) ;
 }
 }
 }
 }
 }