int vp9_get_qindex ( const struct segmentation * seg , int segment_id , int base_qindex ) {
 if ( vp9_segfeature_active ( seg , segment_id , SEG_LVL_ALT_Q ) ) {
 const int data = vp9_get_segdata ( seg , segment_id , SEG_LVL_ALT_Q ) ;
 const int seg_qindex = seg -> abs_delta == SEGMENT_ABSDATA ? data : base_qindex + data ;
 return clamp ( seg_qindex , 0 , MAXQ ) ;
 }
 else {
 return base_qindex ;
 }
 }