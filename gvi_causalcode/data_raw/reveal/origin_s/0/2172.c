static inline int get_bitsz ( GetBitContext * s , int n ) {
 return n ? get_bits ( s , n ) : 0 ;
 }