static inline int asv1_decode_block ( ASV1Context * a , int16_t block [ 64 ] ) {
 int i ;
 block [ 0 ] = 8 * get_bits ( & a -> gb , 8 ) ;
 for ( i = 0 ;
 i < 11 ;
 i ++ ) {
 const int ccp = get_vlc2 ( & a -> gb , ccp_vlc . table , VLC_BITS , 1 ) ;
 if ( ccp ) {
 if ( ccp == 16 ) break ;
 if ( ccp < 0 || i >= 10 ) {
 av_log ( a -> avctx , AV_LOG_ERROR , "coded coeff pattern damaged\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( ccp & 8 ) block [ a -> scantable . permutated [ 4 * i + 0 ] ] = ( asv1_get_level ( & a -> gb ) * a -> intra_matrix [ 4 * i + 0 ] ) >> 4 ;
 if ( ccp & 4 ) block [ a -> scantable . permutated [ 4 * i + 1 ] ] = ( asv1_get_level ( & a -> gb ) * a -> intra_matrix [ 4 * i + 1 ] ) >> 4 ;
 if ( ccp & 2 ) block [ a -> scantable . permutated [ 4 * i + 2 ] ] = ( asv1_get_level ( & a -> gb ) * a -> intra_matrix [ 4 * i + 2 ] ) >> 4 ;
 if ( ccp & 1 ) block [ a -> scantable . permutated [ 4 * i + 3 ] ] = ( asv1_get_level ( & a -> gb ) * a -> intra_matrix [ 4 * i + 3 ] ) >> 4 ;
 }
 }
 return 0 ;
 }