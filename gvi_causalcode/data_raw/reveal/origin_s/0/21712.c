static inline void code_gen_alloc ( size_t tb_size ) {
 tcg_ctx . code_gen_buffer_size = size_code_gen_buffer ( tb_size ) ;
 tcg_ctx . code_gen_buffer = alloc_code_gen_buffer ( ) ;
 if ( tcg_ctx . code_gen_buffer == NULL ) {
 fprintf ( stderr , "Could not allocate dynamic translator buffer\n" ) ;
 exit ( 1 ) ;
 }
 qemu_madvise ( tcg_ctx . code_gen_buffer , tcg_ctx . code_gen_buffer_size , QEMU_MADV_HUGEPAGE ) ;
 tcg_ctx . code_gen_prologue = tcg_ctx . code_gen_buffer + tcg_ctx . code_gen_buffer_size - 1024 ;
 tcg_ctx . code_gen_buffer_size -= 1024 ;
 tcg_ctx . code_gen_buffer_max_size = tcg_ctx . code_gen_buffer_size - ( TCG_MAX_OP_SIZE * OPC_BUF_SIZE ) ;
 tcg_ctx . code_gen_max_blocks = tcg_ctx . code_gen_buffer_size / CODE_GEN_AVG_BLOCK_SIZE ;
 tcg_ctx . tb_ctx . tbs = g_malloc ( tcg_ctx . code_gen_max_blocks * sizeof ( TranslationBlock ) ) ;
 }