static BIGNUM * SRP_gN_place_bn ( STACK_OF ( SRP_gN_cache ) * gN_cache , char * ch ) {
 int i ;
 if ( gN_cache == NULL ) return NULL ;
 for ( i = 0 ;
 i < sk_SRP_gN_cache_num ( gN_cache ) ;
 i ++ ) {
 SRP_gN_cache * cache = sk_SRP_gN_cache_value ( gN_cache , i ) ;
 if ( strcmp ( cache -> b64_bn , ch ) == 0 ) return cache -> bn ;
 }
 {
 SRP_gN_cache * newgN = SRP_gN_new_init ( ch ) ;
 if ( newgN ) {
 if ( sk_SRP_gN_cache_insert ( gN_cache , newgN , 0 ) > 0 ) return newgN -> bn ;
 SRP_gN_free ( newgN ) ;
 }
 }
 return NULL ;
 }