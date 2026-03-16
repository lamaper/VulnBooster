static void write_segment_id ( vp9_writer * w , const struct segmentation * seg , int segment_id ) {
 if ( seg -> enabled && seg -> update_map ) vp9_write_tree ( w , vp9_segment_tree , seg -> tree_probs , segment_id , 3 , 0 ) ;
 }