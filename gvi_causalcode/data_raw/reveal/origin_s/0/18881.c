int cpu_gen_code ( CPUArchState * env , TranslationBlock * tb , int * gen_code_size_ptr ) {
 TCGContext * s = & tcg_ctx ;
 uint8_t * gen_code_buf ;
 int gen_code_size ;


 ti = profile_getclock ( ) ;

 gen_intermediate_code ( env , tb ) ;
 gen_code_buf = tb -> tc_ptr ;
 tb -> tb_next_offset [ 0 ] = 0xffff ;
 tb -> tb_next_offset [ 1 ] = 0xffff ;
 s -> tb_next_offset = tb -> tb_next_offset ;

 s -> tb_next = NULL ;

 s -> tb_next = tb -> tb_next ;

 s -> interm_time += profile_getclock ( ) - ti ;
 s -> code_time -= profile_getclock ( ) ;

 * gen_code_size_ptr = gen_code_size ;

 s -> code_in_len += tb -> size ;
 s -> code_out_len += gen_code_size ;

 qemu_log ( "OUT: [size=%d]\n" , * gen_code_size_ptr ) ;
 log_disas ( tb -> tc_ptr , * gen_code_size_ptr ) ;
 qemu_log ( "\n" ) ;
 qemu_log_flush ( ) ;
 }

 }