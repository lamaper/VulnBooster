void tb_invalidate_phys_page_range ( tb_page_addr_t start , tb_page_addr_t end , int is_cpu_write_access ) {
 TranslationBlock * tb , * tb_next , * saved_tb ;
 CPUArchState * env = cpu_single_env ;
 CPUState * cpu = NULL ;
 tb_page_addr_t tb_start , tb_end ;
 PageDesc * p ;
 int n ;

 TranslationBlock * current_tb = NULL ;
 int current_tb_modified = 0 ;
 target_ulong current_pc = 0 ;
 target_ulong current_cs_base = 0 ;
 int current_flags = 0 ;

 if ( ! p ) {
 return ;
 }
 if ( ! p -> code_bitmap && ++ p -> code_write_count >= SMC_BITMAP_USE_THRESHOLD && is_cpu_write_access ) {
 build_page_bitmap ( p ) ;
 }
 if ( env != NULL ) {
 cpu = ENV_GET_CPU ( env ) ;
 }
 tb = p -> first_tb ;
 while ( tb != NULL ) {
 n = ( uintptr_t ) tb & 3 ;
 tb = ( TranslationBlock * ) ( ( uintptr_t ) tb & ~ 3 ) ;
 tb_next = tb -> page_next [ n ] ;
 if ( n == 0 ) {
 tb_start = tb -> page_addr [ 0 ] + ( tb -> pc & ~ TARGET_PAGE_MASK ) ;
 tb_end = tb_start + tb -> size ;
 }
 else {
 tb_start = tb -> page_addr [ 1 ] ;
 tb_end = tb_start + ( ( tb -> pc + tb -> size ) & ~ TARGET_PAGE_MASK ) ;
 }
 if ( ! ( tb_end <= start || tb_start >= end ) ) {

 current_tb_not_found = 0 ;
 current_tb = NULL ;
 if ( env -> mem_io_pc ) {
 current_tb = tb_find_pc ( env -> mem_io_pc ) ;
 }
 }
 if ( current_tb == tb && ( current_tb -> cflags & CF_COUNT_MASK ) != 1 ) {
 current_tb_modified = 1 ;
 cpu_restore_state_from_tb ( current_tb , env , env -> mem_io_pc ) ;
 cpu_get_tb_cpu_state ( env , & current_pc , & current_cs_base , & current_flags ) ;
 }

 if ( cpu != NULL ) {
 saved_tb = cpu -> current_tb ;
 cpu -> current_tb = NULL ;
 }
 tb_phys_invalidate ( tb , - 1 ) ;
 if ( cpu != NULL ) {
 cpu -> current_tb = saved_tb ;
 if ( cpu -> interrupt_request && cpu -> current_tb ) {
 cpu_interrupt ( cpu , cpu -> interrupt_request ) ;
 }
 }
 }
 tb = tb_next ;
 }

 invalidate_page_bitmap ( p ) ;
 if ( is_cpu_write_access ) {
 tlb_unprotect_code_phys ( env , start , env -> mem_io_vaddr ) ;
 }
 }

 cpu -> current_tb = NULL ;
 tb_gen_code ( env , current_pc , current_cs_base , current_flags , 1 ) ;
 cpu_resume_from_signal ( env , NULL ) ;
 }
