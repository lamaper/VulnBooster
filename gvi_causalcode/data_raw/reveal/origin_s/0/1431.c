static inline int decode_mb ( MDECContext * a , int16_t block [ 6 ] [ 64 ] ) {
 int i , ret ;
 const int block_index [ 6 ] = {
 5 , 4 , 0 , 1 , 2 , 3 }
 ;
 a -> dsp . clear_blocks ( block [ 0 ] ) ;
 for ( i = 0 ;
 i < 6 ;
 i ++ ) {
 if ( ( ret = mdec_decode_block_intra ( a , block [ block_index [ i ] ] , block_index [ i ] ) ) < 0 ) return ret ;
 if ( get_bits_left ( & a -> gb ) < 0 ) return AVERROR_INVALIDDATA ;
 }
 return 0 ;
 }