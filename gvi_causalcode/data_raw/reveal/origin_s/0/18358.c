static inline PageDesc * page_find ( tb_page_addr_t index ) {
 return page_find_alloc ( index , 0 ) ;
 }