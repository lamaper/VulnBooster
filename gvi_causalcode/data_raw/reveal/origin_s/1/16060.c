static __inline__ __u64 __fswab64 ( __u64 val ) {


 __u32 l = val & ( ( 1ULL << 32 ) - 1 ) ;
 return ( ( ( __u64 ) __fswab32 ( l ) ) << 32 ) | ( ( __u64 ) ( __fswab32 ( h ) ) ) ;

