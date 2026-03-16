static void fill_variance_tree ( void * data , BLOCK_SIZE bsize ) {
 variance_node node ;
 tree_to_node ( data , bsize , & node ) ;
 sum_2_variances ( node . split [ 0 ] , node . split [ 1 ] , & node . part_variances -> horz [ 0 ] ) ;
 sum_2_variances ( node . split [ 2 ] , node . split [ 3 ] , & node . part_variances -> horz [ 1 ] ) ;
 sum_2_variances ( node . split [ 0 ] , node . split [ 2 ] , & node . part_variances -> vert [ 0 ] ) ;
 sum_2_variances ( node . split [ 1 ] , node . split [ 3 ] , & node . part_variances -> vert [ 1 ] ) ;
 sum_2_variances ( & node . part_variances -> vert [ 0 ] , & node . part_variances -> vert [ 1 ] , & node . part_variances -> none ) ;
 }