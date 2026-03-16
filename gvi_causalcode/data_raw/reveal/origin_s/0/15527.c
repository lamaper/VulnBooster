static rtmpt_conv_t * rtmpt_init_rconv ( conversation_t * conv ) {
 rtmpt_conv_t * rconv = wmem_new ( wmem_file_scope ( ) , rtmpt_conv_t ) ;
 conversation_add_proto_data ( conv , proto_rtmpt , rconv ) ;
 rconv -> seqs [ 0 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> seqs [ 1 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> frags [ 0 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> frags [ 1 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> ids [ 0 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> ids [ 1 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> packets [ 0 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> packets [ 1 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> chunksize [ 0 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> chunksize [ 1 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> txids [ 0 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 rconv -> txids [ 1 ] = wmem_tree_new ( wmem_file_scope ( ) ) ;
 return rconv ;
 }