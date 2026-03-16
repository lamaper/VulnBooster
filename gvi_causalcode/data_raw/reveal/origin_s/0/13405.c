static void encode_b_rt ( VP9_COMP * cpi , const TileInfo * const tile , TOKENEXTRA * * tp , int mi_row , int mi_col , int output_enabled , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx ) {
 set_offsets ( cpi , tile , mi_row , mi_col , bsize ) ;
 update_state_rt ( cpi , ctx , mi_row , mi_col , bsize ) ;

 vp9_denoiser_denoise ( & cpi -> denoiser , & cpi -> mb , mi_row , mi_col , MAX ( BLOCK_8X8 , bsize ) , ctx ) ;
 }

 update_stats ( & cpi -> common , & cpi -> mb ) ;
 ( * tp ) -> token = EOSB_TOKEN ;
 ( * tp ) ++ ;
 }