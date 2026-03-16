void tb_check_watchpoint ( CPUArchState * env ) {
 TranslationBlock * tb ;
 tb = tb_find_pc ( env -> mem_io_pc ) ;
 if ( ! tb ) {
 cpu_abort ( env , "check_watchpoint: could not find TB for pc=%p" , ( void * ) env -> mem_io_pc ) ;
 }
 cpu_restore_state_from_tb ( tb , env , env -> mem_io_pc ) ;
 tb_phys_invalidate ( tb , - 1 ) ;
 }