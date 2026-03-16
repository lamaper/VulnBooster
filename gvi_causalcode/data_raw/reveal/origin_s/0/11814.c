int compare_key_tok_text ( const void * a1 , const void * a2 ) {
 const struct key_tok * p1 = a1 ;
 const struct key_tok * p2 = a2 ;
 return strcmp ( p1 -> key , p2 -> key ) ;
 }