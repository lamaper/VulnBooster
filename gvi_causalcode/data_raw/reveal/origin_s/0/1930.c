static void cpu_exec_nocache ( CPUArchState * env , int max_cycles , TranslationBlock * orig_tb ) {
 CPUState * cpu = ENV_GET_CPU ( env ) ;
 TranslationBlock * tb ;
 if ( max_cycles > CF_COUNT_MASK ) max_cycles = CF_COUNT_MASK ;
 tb = tb_gen_code ( env , orig_tb -> pc , orig_tb -> cs_base , orig_tb -> flags , max_cycles ) ;
 cpu -> current_tb = tb ;
 cpu_tb_exec ( cpu , tb -> tc_ptr ) ;
 cpu -> current_tb = NULL ;
 tb_phys_invalidate ( tb , - 1 ) ;
 tb_free ( tb ) ;
 }