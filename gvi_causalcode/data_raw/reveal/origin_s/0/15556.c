BN_ULONG bn_div_words ( BN_ULONG h , BN_ULONG l , BN_ULONG d ) {
 BN_ULONG dh , dl , q , ret = 0 , th , tl , t ;
 int i , count = 2 ;
 if ( d == 0 ) return ( BN_MASK2 ) ;
 i = BN_num_bits_word ( d ) ;
 assert ( ( i == BN_BITS2 ) || ( h <= ( BN_ULONG ) 1 << i ) ) ;
 i = BN_BITS2 - i ;
 if ( h >= d ) h -= d ;
 if ( i ) {
 d <<= i ;
 h = ( h << i ) | ( l >> ( BN_BITS2 - i ) ) ;
 l <<= i ;
 }
 dh = ( d & BN_MASK2h ) >> BN_BITS4 ;
 dl = ( d & BN_MASK2l ) ;
 for ( ;
 ;
 ) {
 if ( ( h >> BN_BITS4 ) == dh ) q = BN_MASK2l ;
 else q = h / dh ;
 th = q * dh ;
 tl = dl * q ;
 for ( ;
 ;
 ) {
 t = h - th ;
 if ( ( t & BN_MASK2h ) || ( ( tl ) <= ( ( t << BN_BITS4 ) | ( ( l & BN_MASK2h ) >> BN_BITS4 ) ) ) ) break ;
 q -- ;
 th -= dh ;
 tl -= dl ;
 }
 t = ( tl >> BN_BITS4 ) ;
 tl = ( tl << BN_BITS4 ) & BN_MASK2h ;
 th += t ;
 if ( l < tl ) th ++ ;
 l -= tl ;
 if ( h < th ) {
 h += d ;
 q -- ;
 }
 h -= th ;
 if ( -- count == 0 ) break ;
 ret = q << BN_BITS4 ;
 h = ( ( h << BN_BITS4 ) | ( l >> BN_BITS4 ) ) & BN_MASK2 ;
 l = ( l & BN_MASK2l ) << BN_BITS4 ;
 }
 ret |= q ;
 return ( ret ) ;
 }