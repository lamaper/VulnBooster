static int mss4_decode_dct_block ( MSS4Context * c , GetBitContext * gb , uint8_t * dst [ 3 ] , int mb_x , int mb_y ) {
 int i , j , k , ret ;
 uint8_t * out = dst [ 0 ] ;
 for ( j = 0 ;
 j < 2 ;
 j ++ ) {
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 int xpos = mb_x * 2 + i ;
 c -> dc_cache [ j ] [ TOP_LEFT ] = c -> dc_cache [ j ] [ TOP ] ;
 c -> dc_cache [ j ] [ TOP ] = c -> prev_dc [ 0 ] [ mb_x * 2 + i ] ;
 ret = mss4_decode_dct ( gb , c -> dc_vlc , c -> ac_vlc , c -> block , c -> dc_cache [ j ] , xpos , mb_y * 2 + j , c -> quant_mat [ 0 ] ) ;
 if ( ret ) return ret ;
 c -> prev_dc [ 0 ] [ mb_x * 2 + i ] = c -> dc_cache [ j ] [ LEFT ] ;
 ff_mss34_dct_put ( out + xpos * 8 , c -> pic . linesize [ 0 ] , c -> block ) ;
 }
 out += 8 * c -> pic . linesize [ 0 ] ;
 }
 for ( i = 1 ;
 i < 3 ;
 i ++ ) {
 c -> dc_cache [ i + 1 ] [ TOP_LEFT ] = c -> dc_cache [ i + 1 ] [ TOP ] ;
 c -> dc_cache [ i + 1 ] [ TOP ] = c -> prev_dc [ i ] [ mb_x ] ;
 ret = mss4_decode_dct ( gb , c -> dc_vlc + 1 , c -> ac_vlc + 1 , c -> block , c -> dc_cache [ i + 1 ] , mb_x , mb_y , c -> quant_mat [ 1 ] ) ;
 if ( ret ) return ret ;
 c -> prev_dc [ i ] [ mb_x ] = c -> dc_cache [ i + 1 ] [ LEFT ] ;
 ff_mss34_dct_put ( c -> imgbuf [ i ] , 8 , c -> block ) ;
 out = dst [ i ] + mb_x * 16 ;
 for ( j = 0 ;
 j < 16 ;
 j ++ ) {
 for ( k = 0 ;
 k < 8 ;
 k ++ ) AV_WN16A ( out + k * 2 , c -> imgbuf [ i ] [ k + ( j & ~ 1 ) * 4 ] * 0x101 ) ;
 out += c -> pic . linesize [ i ] ;
 }
 }
 return 0 ;
 }