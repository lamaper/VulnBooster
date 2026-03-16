int vp9_is_skippable_in_plane ( MACROBLOCK * x , BLOCK_SIZE bsize , int plane ) {
 int result = 1 ;
 struct is_skippable_args args = {
 x , & result }
 ;
 vp9_foreach_transformed_block_in_plane ( & x -> e_mbd , bsize , plane , is_skippable , & args ) ;
 return result ;
 }