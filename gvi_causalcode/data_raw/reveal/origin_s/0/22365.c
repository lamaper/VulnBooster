static inline void get_array ( GetBitContext * gb , int * dst , int len , int bits ) {
 while ( len -- ) * dst ++ = get_bits ( gb , bits ) ;
 }