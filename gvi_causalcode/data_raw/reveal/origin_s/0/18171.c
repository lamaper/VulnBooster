void tb_phys_invalidate ( TranslationBlock * tb , tb_page_addr_t page_addr ) {
 CPUArchState * env ;
 PageDesc * p ;
 unsigned int h , n1 ;
 tb_page_addr_t phys_pc ;
 TranslationBlock * tb1 , * tb2 ;
 phys_pc = tb -> page_addr [ 0 ] + ( tb -> pc & ~ TARGET_PAGE_MASK ) ;
 h = tb_phys_hash_func ( phys_pc ) ;
 tb_hash_remove ( & tcg_ctx . tb_ctx . tb_phys_hash [ h ] , tb ) ;
 if ( tb -> page_addr [ 0 ] != page_addr ) {
 p = page_find ( tb -> page_addr [ 0 ] >> TARGET_PAGE_BITS ) ;
 tb_page_remove ( & p -> first_tb , tb ) ;
 invalidate_page_bitmap ( p ) ;
 }
 if ( tb -> page_addr [ 1 ] != - 1 && tb -> page_addr [ 1 ] != page_addr ) {
 p = page_find ( tb -> page_addr [ 1 ] >> TARGET_PAGE_BITS ) ;
 tb_page_remove ( & p -> first_tb , tb ) ;
 invalidate_page_bitmap ( p ) ;
 }
 tcg_ctx . tb_ctx . tb_invalidated_flag = 1 ;
 h = tb_jmp_cache_hash_func ( tb -> pc ) ;
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 if ( env -> tb_jmp_cache [ h ] == tb ) {
 env -> tb_jmp_cache [ h ] = NULL ;
 }
 }
 tb_jmp_remove ( tb , 0 ) ;
 tb_jmp_remove ( tb , 1 ) ;
 tb1 = tb -> jmp_first ;
 for ( ;
 ;
 ) {
 n1 = ( uintptr_t ) tb1 & 3 ;
 if ( n1 == 2 ) {
 break ;
 }
 tb1 = ( TranslationBlock * ) ( ( uintptr_t ) tb1 & ~ 3 ) ;
 tb2 = tb1 -> jmp_next [ n1 ] ;
 tb_reset_jump ( tb1 , n1 ) ;
 tb1 -> jmp_next [ n1 ] = NULL ;
 tb1 = tb2 ;
 }
 tb -> jmp_first = ( TranslationBlock * ) ( ( uintptr_t ) tb | 2 ) ;
 tcg_ctx . tb_ctx . tb_phys_invalidate_count ++ ;
 }