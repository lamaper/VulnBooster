static void rv34_decoder_free ( RV34DecContext * r ) {
 av_freep ( & r -> intra_types_hist ) ;
 r -> intra_types = NULL ;
 av_freep ( & r -> tmp_b_block_base ) ;
 av_freep ( & r -> mb_type ) ;
 av_freep ( & r -> cbp_luma ) ;
 av_freep ( & r -> cbp_chroma ) ;
 av_freep ( & r -> deblock_coefs ) ;
 }