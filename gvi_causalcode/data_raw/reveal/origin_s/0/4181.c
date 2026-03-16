int vp9_decode_block_tokens ( VP9_COMMON * cm , MACROBLOCKD * xd , int plane , int block , BLOCK_SIZE plane_bsize , int x , int y , TX_SIZE tx_size , vp9_reader * r ) {
 struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 const int ctx = get_entropy_context ( tx_size , pd -> above_context + x , pd -> left_context + y ) ;
 const scan_order * so = get_scan ( xd , tx_size , pd -> plane_type , block ) ;
 const int eob = decode_coefs ( cm , xd , pd -> plane_type , BLOCK_OFFSET ( pd -> dqcoeff , block ) , tx_size , pd -> dequant , ctx , so -> scan , so -> neighbors , r ) ;
 vp9_set_contexts ( xd , pd , plane_bsize , tx_size , eob > 0 , x , y ) ;
 return eob ;
 }