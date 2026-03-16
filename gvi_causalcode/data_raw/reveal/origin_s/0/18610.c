static void encode_b ( VP9_COMP * cpi , const TileInfo * const tile , TOKENEXTRA * * tp , int mi_row , int mi_col , int output_enabled , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx ) {
 set_offsets ( cpi , tile , mi_row , mi_col , bsize ) ;
 update_state ( cpi , ctx , mi_row , mi_col , bsize , output_enabled ) ;
 encode_superblock ( cpi , tp , output_enabled , mi_row , mi_col , bsize , ctx ) ;
 if ( output_enabled ) {
 update_stats ( & cpi -> common , & cpi -> mb ) ;
 ( * tp ) -> token = EOSB_TOKEN ;
 ( * tp ) ++ ;
 }
 }