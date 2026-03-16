void vp9_encode_sb ( MACROBLOCK * x , BLOCK_SIZE bsize ) {
 MACROBLOCKD * const xd = & x -> e_mbd ;
 struct optimize_ctx ctx ;
 MB_MODE_INFO * mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 struct encode_b_args arg = {
 x , & ctx , & mbmi -> skip }
 ;
 int plane ;
 mbmi -> skip = 1 ;
 if ( x -> skip ) return ;
 for ( plane = 0 ;
 plane < MAX_MB_PLANE ;
 ++ plane ) {
 if ( ! x -> skip_recode ) vp9_subtract_plane ( x , bsize , plane ) ;
 if ( x -> optimize && ( ! x -> skip_recode || ! x -> skip_optimize ) ) {
 const struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 const TX_SIZE tx_size = plane ? get_uv_tx_size ( mbmi , pd ) : mbmi -> tx_size ;
 vp9_get_entropy_contexts ( bsize , tx_size , pd , ctx . ta [ plane ] , ctx . tl [ plane ] ) ;
 }
 vp9_foreach_transformed_block_in_plane ( xd , bsize , plane , encode_block , & arg ) ;
 }
 }