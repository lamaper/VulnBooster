static void block_rd_txfm ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * arg ) {
 struct rdcost_block_args * args = arg ;
 MACROBLOCK * const x = args -> x ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 int64_t rd1 , rd2 , rd ;
 if ( args -> skip ) return ;
 if ( ! is_inter_block ( mbmi ) ) {
 vp9_encode_block_intra ( x , plane , block , plane_bsize , tx_size , & mbmi -> skip ) ;
 dist_block ( plane , block , tx_size , args ) ;
 }
 else if ( max_txsize_lookup [ plane_bsize ] == tx_size ) {
 if ( x -> skip_txfm [ ( plane << 2 ) + ( block >> ( tx_size << 1 ) ) ] == 0 ) {
 vp9_xform_quant ( x , plane , block , plane_bsize , tx_size ) ;
 dist_block ( plane , block , tx_size , args ) ;
 }
 else if ( x -> skip_txfm [ ( plane << 2 ) + ( block >> ( tx_size << 1 ) ) ] == 2 ) {
 tran_low_t * const coeff = BLOCK_OFFSET ( x -> plane [ plane ] . coeff , block ) ;
 tran_low_t * const dqcoeff = BLOCK_OFFSET ( xd -> plane [ plane ] . dqcoeff , block ) ;
 vp9_xform_quant_dc ( x , plane , block , plane_bsize , tx_size ) ;
 args -> sse = x -> bsse [ ( plane << 2 ) + ( block >> ( tx_size << 1 ) ) ] << 4 ;
 args -> dist = args -> sse ;
 if ( ! x -> plane [ plane ] . eobs [ block ] ) args -> dist = args -> sse - ( ( coeff [ 0 ] * coeff [ 0 ] - ( coeff [ 0 ] - dqcoeff [ 0 ] ) * ( coeff [ 0 ] - dqcoeff [ 0 ] ) ) >> 2 ) ;
 }
 else {
 x -> plane [ plane ] . eobs [ block ] = 0 ;
 args -> sse = x -> bsse [ ( plane << 2 ) + ( block >> ( tx_size << 1 ) ) ] << 4 ;
 args -> dist = args -> sse ;
 }
 }
 else {
 vp9_xform_quant ( x , plane , block , plane_bsize , tx_size ) ;
 dist_block ( plane , block , tx_size , args ) ;
 }
 rate_block ( plane , block , plane_bsize , tx_size , args ) ;
 rd1 = RDCOST ( x -> rdmult , x -> rddiv , args -> rate , args -> dist ) ;
 rd2 = RDCOST ( x -> rdmult , x -> rddiv , 0 , args -> sse ) ;
 rd = MIN ( rd1 , rd2 ) ;
 if ( plane == 0 ) x -> zcoeff_blk [ tx_size ] [ block ] = ! x -> plane [ plane ] . eobs [ block ] || ( rd1 > rd2 && ! xd -> lossless ) ;
 args -> this_rate += args -> rate ;
 args -> this_dist += args -> dist ;
 args -> this_sse += args -> sse ;
 args -> this_rd += rd ;
 if ( args -> this_rd > args -> best_rd ) {
 args -> skip = 1 ;
 return ;
 }
 }