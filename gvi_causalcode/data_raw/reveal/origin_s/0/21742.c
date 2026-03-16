void vp9_foreach_transformed_block ( const MACROBLOCKD * const xd , BLOCK_SIZE bsize , foreach_transformed_block_visitor visit , void * arg ) {
 int plane ;
 for ( plane = 0 ;
 plane < MAX_MB_PLANE ;
 plane ++ ) vp9_foreach_transformed_block_in_plane ( xd , bsize , plane , visit , arg ) ;
 }