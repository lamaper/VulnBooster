void tb_free ( TranslationBlock * tb ) {
 if ( tcg_ctx . tb_ctx . nb_tbs > 0 && tb == & tcg_ctx . tb_ctx . tbs [ tcg_ctx . tb_ctx . nb_tbs - 1 ] ) {
 tcg_ctx . code_gen_ptr = tb -> tc_ptr ;
 tcg_ctx . tb_ctx . nb_tbs -- ;
 }
 }