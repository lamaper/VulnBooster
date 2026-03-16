void vp9_regular_quantize_b_4x4 ( MACROBLOCK * x , int plane , int block , const int16_t * scan , const int16_t * iscan ) {
 MACROBLOCKD * const xd = & x -> e_mbd ;
 struct macroblock_plane * p = & x -> plane [ plane ] ;
 struct macroblockd_plane * pd = & xd -> plane [ plane ] ;
 vp9_quantize_b ( BLOCK_OFFSET ( p -> coeff , block ) , 16 , x -> skip_block , p -> zbin , p -> round , p -> quant , p -> quant_shift , BLOCK_OFFSET ( p -> qcoeff , block ) , BLOCK_OFFSET ( pd -> dqcoeff , block ) , pd -> dequant , p -> zbin_extra , & p -> eobs [ block ] , scan , iscan ) ;
 }