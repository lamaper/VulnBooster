void tb_flush ( CPUArchState * env1 ) {
 CPUArchState * env ;


 cpu_abort ( env1 , "Internal error: code buffer overflow\n" ) ;
 }
 tcg_ctx . tb_ctx . nb_tbs = 0 ;
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 memset ( env -> tb_jmp_cache , 0 , TB_JMP_CACHE_SIZE * sizeof ( void * ) ) ;
 }
 memset ( tcg_ctx . tb_ctx . tb_phys_hash , 0 , CODE_GEN_PHYS_HASH_SIZE * sizeof ( void * ) ) ;
 page_flush_tb ( ) ;
 tcg_ctx . code_gen_ptr = tcg_ctx . code_gen_buffer ;
 tcg_ctx . tb_ctx . tb_flush_count ++ ;
 }