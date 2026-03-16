static void is_skippable ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * argv ) {
 struct is_skippable_args * args = argv ;
 ( void ) plane_bsize ;
 ( void ) tx_size ;
 args -> skippable [ 0 ] &= ( ! args -> x -> plane [ plane ] . eobs [ block ] ) ;
 }