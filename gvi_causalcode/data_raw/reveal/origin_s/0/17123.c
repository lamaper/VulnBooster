void vp9_disable_segmentation ( struct segmentation * seg ) {
 seg -> enabled = 0 ;
 seg -> update_map = 0 ;
 seg -> update_data = 0 ;
 }