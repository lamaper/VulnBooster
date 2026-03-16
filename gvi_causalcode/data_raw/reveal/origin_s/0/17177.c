static int tqi_decode_mb ( MpegEncContext * s , int16_t ( * block ) [ 64 ] ) {
 int n ;
 s -> dsp . clear_blocks ( block [ 0 ] ) ;
 for ( n = 0 ;
 n < 6 ;
 n ++ ) if ( ff_mpeg1_decode_block_intra ( s , block [ n ] , n ) < 0 ) return - 1 ;
 return 0 ;
 }