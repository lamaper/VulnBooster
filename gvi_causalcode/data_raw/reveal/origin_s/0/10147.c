void vp9_enable_segmentation ( struct segmentation * seg ) {
 seg -> enabled = 1 ;
 seg -> update_map = 1 ;
 seg -> update_data = 1 ;
 }