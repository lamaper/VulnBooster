void tb_invalidate_phys_range ( tb_page_addr_t start , tb_page_addr_t end , int is_cpu_write_access ) {
 while ( start < end ) {
 tb_invalidate_phys_page_range ( start , end , is_cpu_write_access ) ;
 start &= TARGET_PAGE_MASK ;
 start += TARGET_PAGE_SIZE ;
 }
 }