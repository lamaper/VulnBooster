void tb_flush_jmp_cache ( CPUArchState * env , target_ulong addr ) {
 unsigned int i ;
 i = tb_jmp_cache_hash_page ( addr - TARGET_PAGE_SIZE ) ;
 memset ( & env -> tb_jmp_cache [ i ] , 0 , TB_JMP_PAGE_SIZE * sizeof ( TranslationBlock * ) ) ;
 i = tb_jmp_cache_hash_page ( addr ) ;
 memset ( & env -> tb_jmp_cache [ i ] , 0 , TB_JMP_PAGE_SIZE * sizeof ( TranslationBlock * ) ) ;
 }