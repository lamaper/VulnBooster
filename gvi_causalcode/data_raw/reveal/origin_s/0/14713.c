static inline int get_scale ( GetBitContext * gb , int level , int value , int log2range ) {
 if ( level < 5 ) {
 value += get_bitalloc ( gb , & dca_scalefactor , level ) ;
 value = av_clip ( value , 0 , ( 1 << log2range ) - 1 ) ;
 }
 else if ( level < 8 ) {
 if ( level + 1 > log2range ) {
 skip_bits ( gb , level + 1 - log2range ) ;
 value = get_bits ( gb , log2range ) ;
 }
 else {
 value = get_bits ( gb , level + 1 ) ;
 }
 }
 return value ;
 }