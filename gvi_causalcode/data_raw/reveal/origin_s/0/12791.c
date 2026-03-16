static void decode_dct_block ( RangeCoder * c , DCTBlockCoder * bc , uint8_t * dst , int stride , int block_size , int * block , int mb_x , int mb_y ) {
 int i , j ;
 int bx , by ;
 int nblocks = block_size >> 3 ;
 bx = mb_x * nblocks ;
 by = mb_y * nblocks ;
 for ( j = 0 ;
 j < nblocks ;
 j ++ ) {
 for ( i = 0 ;
 i < nblocks ;
 i ++ ) {
 if ( decode_dct ( c , bc , block , bx + i , by + j ) ) {
 c -> got_error = 1 ;
 return ;
 }
 ff_mss34_dct_put ( dst + i * 8 , stride , block ) ;
 }
 dst += 8 * stride ;
 }
 }