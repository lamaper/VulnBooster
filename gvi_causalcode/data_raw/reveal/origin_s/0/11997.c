static inline void decode8x8 ( GetBitContext * gb , uint8_t * dst , int linesize , DSPContext * dsp ) {
 int i , j , v [ 2 ] ;
 switch ( get_bits ( gb , 2 ) ) {
 case 1 : v [ 0 ] = get_bits ( gb , 8 ) ;
 dsp -> fill_block_tab [ 1 ] ( dst , v [ 0 ] , linesize , 8 ) ;
 break ;
 case 2 : v [ 0 ] = get_bits ( gb , 8 ) ;
 v [ 1 ] = get_bits ( gb , 8 ) ;
 for ( j = 7 ;
 j >= 0 ;
 j -- ) for ( i = 0 ;
 i < 8 ;
 i ++ ) dst [ j * linesize + i ] = v [ get_bits1 ( gb ) ] ;
 break ;
 case 3 : for ( j = 0 ;
 j < 8 ;
 j += 4 ) for ( i = 0 ;
 i < 8 ;
 i += 4 ) decode4x4 ( gb , dst + j * linesize + i , linesize ) ;
 }
 }