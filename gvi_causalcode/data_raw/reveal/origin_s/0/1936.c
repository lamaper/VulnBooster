static int32_t U_CALLCONV compareFallbacks ( const void * context , const void * fb1 , const void * fb2 ) {
 ( void ) context ;
 return ( ( const _MBCSToUFallback * ) fb1 ) -> offset - ( ( const _MBCSToUFallback * ) fb2 ) -> offset ;
 }