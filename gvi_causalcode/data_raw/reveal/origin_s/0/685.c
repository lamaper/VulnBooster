void vp9_encode_block_intra ( MACROBLOCK * x , int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , int8_t * skip ) {
 struct encode_b_args arg = {
 x , NULL , skip }
 ;
 encode_block_intra ( plane , block , plane_bsize , tx_size , & arg ) ;
 }