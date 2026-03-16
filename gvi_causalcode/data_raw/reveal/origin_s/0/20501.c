void tcg_exec_init ( unsigned long tb_size ) {
 cpu_gen_init ( ) ;
 code_gen_alloc ( tb_size ) ;
 tcg_ctx . code_gen_ptr = tcg_ctx . code_gen_buffer ;
 tcg_register_jit ( tcg_ctx . code_gen_buffer , tcg_ctx . code_gen_buffer_size ) ;
 page_init ( ) ;

