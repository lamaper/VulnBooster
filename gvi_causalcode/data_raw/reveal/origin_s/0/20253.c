void vp9_encode_sby_pass1 ( MACROBLOCK * x , BLOCK_SIZE bsize ) {
 vp9_subtract_plane ( x , bsize , 0 ) ;
 vp9_foreach_transformed_block_in_plane ( & x -> e_mbd , bsize , 0 , encode_block_pass1 , x ) ;
 }