static inline void decode2x2 ( GetBitContext * gb , uint8_t * dst , int linesize ) {
 int i , j , v [ 2 ] ;
 switch ( get_bits ( gb , 2 ) ) {
 case 1 : v [ 0 ] = get_bits ( gb , 8 ) ;
 for ( j = 0 ;
 j < 2 ;
 j ++ ) memset ( dst + j * linesize , v [ 0 ] , 2 ) ;
 break ;
 case 2 : v [ 0 ] = get_bits ( gb , 8 ) ;
 v [ 1 ] = get_bits ( gb , 8 ) ;
 for ( j = 0 ;
 j < 2 ;
 j ++ ) for ( i = 0 ;
 i < 2 ;
 i ++ ) dst [ j * linesize + i ] = v [ get_bits1 ( gb ) ] ;
 break ;
 case 3 : for ( j = 0 ;
 j < 2 ;
 j ++ ) for ( i = 0 ;
 i < 2 ;
 i ++ ) dst [ j * linesize + i ] = get_bits ( gb , 8 ) ;
 }
 }