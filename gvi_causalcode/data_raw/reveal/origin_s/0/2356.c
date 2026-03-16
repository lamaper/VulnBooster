static inline void bit_copy ( PutBitContext * pb , GetBitContext * gb ) {
 int bits_left = get_bits_left ( gb ) ;
 while ( bits_left >= MIN_CACHE_BITS ) {
 put_bits ( pb , MIN_CACHE_BITS , get_bits ( gb , MIN_CACHE_BITS ) ) ;
 bits_left -= MIN_CACHE_BITS ;
 }
 if ( bits_left > 0 ) {
 put_bits ( pb , bits_left , get_bits ( gb , bits_left ) ) ;
 }
 }