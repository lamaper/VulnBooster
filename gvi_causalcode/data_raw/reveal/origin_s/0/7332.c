void tb_invalidate_phys_page_fast ( tb_page_addr_t start , int len ) {
 PageDesc * p ;
 int offset , b ;

 qemu_log ( "modifying code at 0x%x size=%d EIP=%x PC=%08x\n" , cpu_single_env -> mem_io_vaddr , len , cpu_single_env -> eip , cpu_single_env -> eip + ( intptr_t ) cpu_single_env -> segs [ R_CS ] . base ) ;
 }

 if ( ! p ) {
 return ;
 }
 if ( p -> code_bitmap ) {
 offset = start & ~ TARGET_PAGE_MASK ;
 b = p -> code_bitmap [ offset >> 3 ] >> ( offset & 7 ) ;
 if ( b & ( ( 1 << len ) - 1 ) ) {
 goto do_invalidate ;
 }
 }
 else {
 do_invalidate : tb_invalidate_phys_page_range ( start , start + len , 1 ) ;
 }
 }