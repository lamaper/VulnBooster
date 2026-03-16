static inline void tb_jmp_remove ( TranslationBlock * tb , int n ) {
 TranslationBlock * tb1 , * * ptb ;
 unsigned int n1 ;
 ptb = & tb -> jmp_next [ n ] ;
 tb1 = * ptb ;
 if ( tb1 ) {
 for ( ;
 ;
 ) {
 tb1 = * ptb ;
 n1 = ( uintptr_t ) tb1 & 3 ;
 tb1 = ( TranslationBlock * ) ( ( uintptr_t ) tb1 & ~ 3 ) ;
 if ( n1 == n && tb1 == tb ) {
 break ;
 }
 if ( n1 == 2 ) {
 ptb = & tb1 -> jmp_first ;
 }
 else {
 ptb = & tb1 -> jmp_next [ n1 ] ;
 }
 }
 * ptb = tb -> jmp_next [ n ] ;
 tb -> jmp_next [ n ] = NULL ;
 }
 }