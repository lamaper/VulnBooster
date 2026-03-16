void vp9_reset_segment_features ( struct segmentation * seg ) {
 seg -> enabled = 0 ;
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 vpx_memset ( seg -> tree_probs , 255 , sizeof ( seg -> tree_probs ) ) ;
 vp9_clearall_segfeatures ( seg ) ;
 }