static inline void tb_page_remove ( TranslationBlock * * ptb , TranslationBlock * tb ) {
 TranslationBlock * tb1 ;
 unsigned int n1 ;
 for ( ;
 ;
 ) {
 tb1 = * ptb ;
 n1 = ( uintptr_t ) tb1 & 3 ;
 tb1 = ( TranslationBlock * ) ( ( uintptr_t ) tb1 & ~ 3 ) ;
 if ( tb1 == tb ) {
 * ptb = tb1 -> page_next [ n1 ] ;
 break ;
 }
 ptb = & tb1 -> page_next [ n1 ] ;
 }
 }