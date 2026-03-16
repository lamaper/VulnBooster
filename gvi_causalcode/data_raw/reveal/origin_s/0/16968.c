static inline int asv2_get_bits ( GetBitContext * gb , int n ) {
 return ff_reverse [ get_bits ( gb , n ) << ( 8 - n ) ] ;
 }