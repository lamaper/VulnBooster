static void dist_block ( int plane , int block , TX_SIZE tx_size , struct rdcost_block_args * args ) {
 const int ss_txfrm_size = tx_size << 1 ;
 MACROBLOCK * const x = args -> x ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct macroblock_plane * const p = & x -> plane [ plane ] ;
 const struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 int64_t this_sse ;
 int shift = tx_size == TX_32X32 ? 0 : 2 ;
 tran_low_t * const coeff = BLOCK_OFFSET ( p -> coeff , block ) ;
 tran_low_t * const dqcoeff = BLOCK_OFFSET ( pd -> dqcoeff , block ) ;
 args -> dist = vp9_block_error ( coeff , dqcoeff , 16 << ss_txfrm_size , & this_sse ) >> shift ;
 args -> sse = this_sse >> shift ;
 if ( x -> skip_encode && ! is_inter_block ( & xd -> mi [ 0 ] . src_mi -> mbmi ) ) {
 int64_t p = ( pd -> dequant [ 1 ] * pd -> dequant [ 1 ] * ( 1 << ss_txfrm_size ) ) >> ( shift + 2 ) ;
 args -> dist += ( p >> 4 ) ;
 args -> sse += p ;
 }
 }