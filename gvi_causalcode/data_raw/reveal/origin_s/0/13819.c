TranslationBlock * tb_gen_code ( CPUArchState * env , target_ulong pc , target_ulong cs_base , int flags , int cflags ) {
 TranslationBlock * tb ;
 uint8_t * tc_ptr ;
 tb_page_addr_t phys_pc , phys_page2 ;
 target_ulong virt_page2 ;
 int code_gen_size ;
 phys_pc = get_page_addr_code ( env , pc ) ;
 tb = tb_alloc ( pc ) ;
 if ( ! tb ) {
 tb_flush ( env ) ;
 tb = tb_alloc ( pc ) ;
 tcg_ctx . tb_ctx . tb_invalidated_flag = 1 ;
 }
 tc_ptr = tcg_ctx . code_gen_ptr ;
 tb -> tc_ptr = tc_ptr ;
 tb -> cs_base = cs_base ;
 tb -> flags = flags ;
 tb -> cflags = cflags ;
 cpu_gen_code ( env , tb , & code_gen_size ) ;
 tcg_ctx . code_gen_ptr = ( void * ) ( ( ( uintptr_t ) tcg_ctx . code_gen_ptr + code_gen_size + CODE_GEN_ALIGN - 1 ) & ~ ( CODE_GEN_ALIGN - 1 ) ) ;
 virt_page2 = ( pc + tb -> size - 1 ) & TARGET_PAGE_MASK ;
 phys_page2 = - 1 ;
 if ( ( pc & TARGET_PAGE_MASK ) != virt_page2 ) {
 phys_page2 = get_page_addr_code ( env , virt_page2 ) ;
 }
 tb_link_page ( tb , phys_pc , phys_page2 ) ;
 return tb ;
 }