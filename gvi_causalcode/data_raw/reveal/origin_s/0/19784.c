static void setup_segmentation ( struct segmentation * seg , struct vp9_read_bit_buffer * rb ) {
 int i , j ;
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 seg -> enabled = vp9_rb_read_bit ( rb ) ;
 if ( ! seg -> enabled ) return ;
 seg -> update_map = vp9_rb_read_bit ( rb ) ;
 if ( seg -> update_map ) {
 for ( i = 0 ;
 i < SEG_TREE_PROBS ;
 i ++ ) seg -> tree_probs [ i ] = vp9_rb_read_bit ( rb ) ? vp9_rb_read_literal ( rb , 8 ) : MAX_PROB ;
 seg -> temporal_update = vp9_rb_read_bit ( rb ) ;
 if ( seg -> temporal_update ) {
 for ( i = 0 ;
 i < PREDICTION_PROBS ;
 i ++ ) seg -> pred_probs [ i ] = vp9_rb_read_bit ( rb ) ? vp9_rb_read_literal ( rb , 8 ) : MAX_PROB ;
 }
 else {
 for ( i = 0 ;
 i < PREDICTION_PROBS ;
 i ++ ) seg -> pred_probs [ i ] = MAX_PROB ;
 }
 }
 seg -> update_data = vp9_rb_read_bit ( rb ) ;
 if ( seg -> update_data ) {
 seg -> abs_delta = vp9_rb_read_bit ( rb ) ;
 vp9_clearall_segfeatures ( seg ) ;
 for ( i = 0 ;
 i < MAX_SEGMENTS ;
 i ++ ) {
 for ( j = 0 ;
 j < SEG_LVL_MAX ;
 j ++ ) {
 int data = 0 ;
 const int feature_enabled = vp9_rb_read_bit ( rb ) ;
 if ( feature_enabled ) {
 vp9_enable_segfeature ( seg , i , j ) ;
 data = decode_unsigned_max ( rb , vp9_seg_feature_data_max ( j ) ) ;
 if ( vp9_is_segfeature_signed ( j ) ) data = vp9_rb_read_bit ( rb ) ? - data : data ;
 }
 vp9_set_segdata ( seg , i , j , data ) ;
 }
 }
 }
 }