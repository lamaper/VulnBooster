static inline void tb_hash_remove ( TranslationBlock * * ptb , TranslationBlock * tb ) {
 TranslationBlock * tb1 ;
 for ( ;
 ;
 ) {
 tb1 = * ptb ;
 if ( tb1 == tb ) {
 * ptb = tb1 -> phys_hash_next ;
 break ;
 }
 ptb = & tb1 -> phys_hash_next ;
 }
 }