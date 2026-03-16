void vp9_clear_segdata ( struct segmentation * seg , int segment_id , SEG_LVL_FEATURES feature_id ) {
 seg -> feature_data [ segment_id ] [ feature_id ] = 0 ;
 }