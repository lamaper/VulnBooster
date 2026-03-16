static int32_t compareFallbacks ( const void * context , const void * fb1 , const void * fb2 ) {
 return ( ( const _MBCSToUFallback * ) fb1 ) -> offset - ( ( const _MBCSToUFallback * ) fb2 ) -> offset ;
 }