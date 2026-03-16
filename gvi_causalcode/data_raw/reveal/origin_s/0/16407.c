static inline void decode_coeff ( int16_t * dst , int coef , int esc , GetBitContext * gb , VLC * vlc , int q ) {
 if ( coef ) {
 if ( coef == esc ) {
 coef = get_vlc2 ( gb , vlc -> table , 9 , 2 ) ;
 if ( coef > 23 ) {
 coef -= 23 ;
 coef = 22 + ( ( 1 << coef ) | get_bits ( gb , coef ) ) ;
 }
 coef += esc ;
 }
 if ( get_bits1 ( gb ) ) coef = - coef ;
 * dst = ( coef * q + 8 ) >> 4 ;
 }
 }