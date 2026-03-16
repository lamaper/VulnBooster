static inline int encode_bgra_bitstream ( HYuvContext * s , int count , int planes ) {
 int i ;
 if ( s -> pb . buf_end - s -> pb . buf - ( put_bits_count ( & s -> pb ) >> 3 ) < 4 * planes * count ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "encoded frame too large\n" ) ;
 return - 1 ;
 }

 \ int b = ( s -> temp [ 0 ] [ planes == 3 ? 3 * i + 2 : 4 * i + B ] - g ) & 0xff ;
 \ int r = ( s -> temp [ 0 ] [ planes == 3 ? 3 * i + 0 : 4 * i + R ] - g ) & 0xff ;
 \ int a = s -> temp [ 0 ] [ planes * i + A ] ;

 \ s -> stats [ 1 ] [ g ] ++ ;
 \ s -> stats [ 2 ] [ r ] ++ ;
 \ if ( planes == 4 ) s -> stats [ 2 ] [ a ] ++ ;

 \ put_bits ( & s -> pb , s -> len [ 0 ] [ b ] , s -> bits [ 0 ] [ b ] ) ;
 \ put_bits ( & s -> pb , s -> len [ 2 ] [ r ] , s -> bits [ 2 ] [ r ] ) ;
 \ if ( planes == 4 ) put_bits ( & s -> pb , s -> len [ 2 ] [ a ] , s -> bits [ 2 ] [ a ] ) ;
 if ( ( s -> flags & CODEC_FLAG_PASS1 ) && ( s -> avctx -> flags2 & CODEC_FLAG2_NO_OUTPUT ) ) {
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 LOAD3 ;
 STAT3 ;
 }
 }
 else if ( s -> context || ( s -> flags & CODEC_FLAG_PASS1 ) ) {
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 LOAD3 ;
 STAT3 ;
 WRITE3 ;
 }
 }
 else {
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 LOAD3 ;
 WRITE3 ;
 }
 }
 return 0 ;
 }