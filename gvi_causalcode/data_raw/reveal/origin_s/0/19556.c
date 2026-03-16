static int cpu_restore_state_from_tb ( TranslationBlock * tb , CPUArchState * env , uintptr_t searched_pc ) {
 TCGContext * s = & tcg_ctx ;
 int j ;
 uintptr_t tc_ptr ;



 gen_intermediate_code_pc ( env , tb ) ;
 if ( use_icount ) {
 env -> icount_decr . u16 . low += tb -> icount ;
 env -> can_do_io = 0 ;
 }
 tc_ptr = ( uintptr_t ) tb -> tc_ptr ;
 if ( searched_pc < tc_ptr ) return - 1 ;
 s -> tb_next_offset = tb -> tb_next_offset ;

 s -> tb_next = NULL ;

 s -> tb_next = tb -> tb_next ;

 if ( j < 0 ) return - 1 ;
 while ( s -> gen_opc_instr_start [ j ] == 0 ) {
 j -- ;
 }
 env -> icount_decr . u16 . low -= s -> gen_opc_icount [ j ] ;
 restore_state_to_opc ( env , tb , j ) ;

 s -> restore_count ++ ;

 }