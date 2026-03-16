static subpicture_t * DecodeBlock ( decoder_t * p_dec , block_t * * pp_block ) {
 subpicture_t * p_spu ;
 block_t * p_block ;
 if ( ! pp_block || * pp_block == NULL ) return NULL ;
 p_block = * pp_block ;
 if ( p_block -> i_flags & ( BLOCK_FLAG_DISCONTINUITY | BLOCK_FLAG_CORRUPTED ) ) {
 block_Release ( p_block ) ;
 return NULL ;
 }
 p_spu = ParseText ( p_dec , p_block ) ;
 block_Release ( p_block ) ;
 * pp_block = NULL ;
 return p_spu ;
 }