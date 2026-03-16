static void encode_segmentation ( VP9_COMMON * cm , MACROBLOCKD * xd , struct vp9_write_bit_buffer * wb ) {
 int i , j ;
 const struct segmentation * seg = & cm -> seg ;
 vp9_wb_write_bit ( wb , seg -> enabled ) ;
 if ( ! seg -> enabled ) return ;
 vp9_wb_write_bit ( wb , seg -> update_map ) ;
 if ( seg -> update_map ) {
 vp9_choose_segmap_coding_method ( cm , xd ) ;
 for ( i = 0 ;
 i < SEG_TREE_PROBS ;
 i ++ ) {
 const int prob = seg -> tree_probs [ i ] ;
 const int update = prob != MAX_PROB ;
 vp9_wb_write_bit ( wb , update ) ;
 if ( update ) vp9_wb_write_literal ( wb , prob , 8 ) ;
 }
 vp9_wb_write_bit ( wb , seg -> temporal_update ) ;
 if ( seg -> temporal_update ) {
 for ( i = 0 ;
 i < PREDICTION_PROBS ;
 i ++ ) {
 const int prob = seg -> pred_probs [ i ] ;
 const int update = prob != MAX_PROB ;
 vp9_wb_write_bit ( wb , update ) ;
 if ( update ) vp9_wb_write_literal ( wb , prob , 8 ) ;
 }
 }
 }
 vp9_wb_write_bit ( wb , seg -> update_data ) ;
 if ( seg -> update_data ) {
 vp9_wb_write_bit ( wb , seg -> abs_delta ) ;
 for ( i = 0 ;
 i < MAX_SEGMENTS ;
 i ++ ) {
 for ( j = 0 ;
 j < SEG_LVL_MAX ;
 j ++ ) {
 const int active = vp9_segfeature_active ( seg , i , j ) ;
 vp9_wb_write_bit ( wb , active ) ;
 if ( active ) {
 const int data = vp9_get_segdata ( seg , i , j ) ;
 const int data_max = vp9_seg_feature_data_max ( j ) ;
 if ( vp9_is_segfeature_signed ( j ) ) {
 encode_unsigned_max ( wb , abs ( data ) , data_max ) ;
 vp9_wb_write_bit ( wb , data < 0 ) ;
 }
 else {
 encode_unsigned_max ( wb , data , data_max ) ;
 }
 }
 }
 }
 }
 }