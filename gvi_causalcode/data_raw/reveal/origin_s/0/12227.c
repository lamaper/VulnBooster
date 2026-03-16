static __always_inline __be16 __cpu_to_be16p ( const __u16 * p ) {
 return ( __be16 ) __swab16p ( p ) ;
 }