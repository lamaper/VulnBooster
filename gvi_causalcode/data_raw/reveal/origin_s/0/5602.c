static __always_inline __be64 __cpu_to_be64p ( const __u64 * p ) {
 return ( __be64 ) __swab64p ( p ) ;
 }