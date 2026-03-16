static void build_page_bitmap ( PageDesc * p ) {
 int n , tb_start , tb_end ;
 TranslationBlock * tb ;
 p -> code_bitmap = g_malloc0 ( TARGET_PAGE_SIZE / 8 ) ;
 tb = p -> first_tb ;
 while ( tb != NULL ) {
 n = ( uintptr_t ) tb & 3 ;
 tb = ( TranslationBlock * ) ( ( uintptr_t ) tb & ~ 3 ) ;
 if ( n == 0 ) {
 tb_start = tb -> pc & ~ TARGET_PAGE_MASK ;
 tb_end = tb_start + tb -> size ;
 if ( tb_end > TARGET_PAGE_SIZE ) {
 tb_end = TARGET_PAGE_SIZE ;
 }
 }
 else {
 tb_start = 0 ;
 tb_end = ( ( tb -> pc + tb -> size ) & ~ TARGET_PAGE_MASK ) ;
 }
 set_bits ( p -> code_bitmap , tb_start , tb_end - tb_start ) ;
 tb = tb -> page_next [ n ] ;
 }
 }