static inline void decode_dc_coeffs ( GetBitContext * gb , int16_t * out , int nblocks ) {
 int16_t prev_dc ;
 int i , sign ;
 int16_t delta ;
 unsigned int code ;
 code = decode_vlc_codeword ( gb , FIRST_DC_CB ) ;
 out [ 0 ] = prev_dc = TOSIGNED ( code ) ;
 out += 64 ;
 delta = 3 ;
 for ( i = 1 ;
 i < nblocks ;
 i ++ , out += 64 ) {
 code = decode_vlc_codeword ( gb , ff_prores_dc_codebook [ FFMIN ( FFABS ( delta ) , 3 ) ] ) ;
 sign = - ( ( ( delta >> 15 ) & 1 ) ^ ( code & 1 ) ) ;
 delta = ( ( ( code + 1 ) >> 1 ) ^ sign ) - sign ;
 prev_dc += delta ;
 out [ 0 ] = prev_dc ;
 }
 }