static inline void tb_alloc_page ( TranslationBlock * tb , unsigned int n , tb_page_addr_t page_addr ) {
 PageDesc * p ;


 p = page_find_alloc ( page_addr >> TARGET_PAGE_BITS , 1 ) ;
 tb -> page_next [ n ] = p -> first_tb ;


 invalidate_page_bitmap ( p ) ;

 target_ulong addr ;
 PageDesc * p2 ;
 int prot ;
 page_addr &= qemu_host_page_mask ;
 prot = 0 ;
 for ( addr = page_addr ;
 addr < page_addr + qemu_host_page_size ;
 addr += TARGET_PAGE_SIZE ) {
 p2 = page_find ( addr >> TARGET_PAGE_BITS ) ;
 if ( ! p2 ) {
 continue ;
 }
 prot |= p2 -> flags ;
 p2 -> flags &= ~ PAGE_WRITE ;
 }
 mprotect ( g2h ( page_addr ) , qemu_host_page_size , ( prot & PAGE_BITS ) & ~ PAGE_WRITE ) ;



 tlb_protect_code ( page_addr ) ;
 }
