void vp9_disable_segfeature ( struct segmentation * seg , int segment_id , SEG_LVL_FEATURES feature_id ) {
 seg -> feature_mask [ segment_id ] &= ~ ( 1 << feature_id ) ;
 }