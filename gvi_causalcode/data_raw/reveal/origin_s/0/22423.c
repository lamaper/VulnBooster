ptvcursor_t * ptvcursor_new ( proto_tree * tree , tvbuff_t * tvb , gint offset ) {
 ptvcursor_t * ptvc ;
 ptvc = ( ptvcursor_t * ) wmem_alloc ( wmem_packet_scope ( ) , sizeof ( ptvcursor_t ) ) ;
 ptvc -> tree = tree ;
 ptvc -> tvb = tvb ;
 ptvc -> offset = offset ;
 ptvc -> pushed_tree = NULL ;
 ptvc -> pushed_tree_max = 0 ;
 ptvc -> pushed_tree_index = 0 ;
 return ptvc ;
 }