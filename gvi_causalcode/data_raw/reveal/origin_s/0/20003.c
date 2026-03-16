static void tb_link_page ( TranslationBlock * tb , tb_page_addr_t phys_pc , tb_page_addr_t phys_page2 ) {
 unsigned int h ;
 TranslationBlock * * ptb ;
 mmap_lock ( ) ;
 h = tb_phys_hash_func ( phys_pc ) ;
 ptb = & tcg_ctx . tb_ctx . tb_phys_hash [ h ] ;
 tb -> phys_hash_next = * ptb ;
 * ptb = tb ;
 tb_alloc_page ( tb , 0 , phys_pc & TARGET_PAGE_MASK ) ;
 if ( phys_page2 != - 1 ) {
 tb_alloc_page ( tb , 1 , phys_page2 ) ;
 }
 else {
 tb -> page_addr [ 1 ] = - 1 ;
 }
 tb -> jmp_first = ( TranslationBlock * ) ( ( uintptr_t ) tb | 2 ) ;
 tb -> jmp_next [ 0 ] = NULL ;
 tb -> jmp_next [ 1 ] = NULL ;
 if ( tb -> tb_next_offset [ 0 ] != 0xffff ) {
 tb_reset_jump ( tb , 0 ) ;
 }
 if ( tb -> tb_next_offset [ 1 ] != 0xffff ) {
 tb_reset_jump ( tb , 1 ) ;
 }


 }