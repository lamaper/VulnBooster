static void tb_invalidate_phys_page ( tb_page_addr_t addr , uintptr_t pc , void * puc ) {
 TranslationBlock * tb ;
 PageDesc * p ;
 int n ;

 CPUState * cpu = current_cpu ;
 CPUArchState * env = NULL ;
 int current_tb_modified = 0 ;
 target_ulong current_pc = 0 ;
 target_ulong current_cs_base = 0 ;
 int current_flags = 0 ;

 p = page_find ( addr >> TARGET_PAGE_BITS ) ;
 if ( ! p ) {
 return ;
 }
 tb = p -> first_tb ;

 current_tb = tb_find_pc ( pc ) ;
 }
 if ( cpu != NULL ) {
 env = cpu -> env_ptr ;
 }

 n = ( uintptr_t ) tb & 3 ;
 tb = ( TranslationBlock * ) ( ( uintptr_t ) tb & ~ 3 ) ;

 current_tb_modified = 1 ;
 cpu_restore_state_from_tb ( current_tb , env , pc ) ;
 cpu_get_tb_cpu_state ( env , & current_pc , & current_cs_base , & current_flags ) ;
 }

 tb = tb -> page_next [ n ] ;
 }
 p -> first_tb = NULL ;

 cpu -> current_tb = NULL ;
 tb_gen_code ( env , current_pc , current_cs_base , current_flags , 1 ) ;
 cpu_resume_from_signal ( env , puc ) ;
 }
