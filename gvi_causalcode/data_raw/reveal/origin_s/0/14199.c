static void inverse_quant ( int16_t * cur_lsp , int16_t * prev_lsp , uint8_t * lsp_index , int bad_frame ) {
 int min_dist , pred ;
 int i , j , temp , stable ;
 if ( ! bad_frame ) {
 min_dist = 0x100 ;
 pred = 12288 ;
 }
 else {
 min_dist = 0x200 ;
 pred = 23552 ;
 lsp_index [ 0 ] = lsp_index [ 1 ] = lsp_index [ 2 ] = 0 ;
 }
 cur_lsp [ 0 ] = lsp_band0 [ lsp_index [ 0 ] ] [ 0 ] ;
 cur_lsp [ 1 ] = lsp_band0 [ lsp_index [ 0 ] ] [ 1 ] ;
 cur_lsp [ 2 ] = lsp_band0 [ lsp_index [ 0 ] ] [ 2 ] ;
 cur_lsp [ 3 ] = lsp_band1 [ lsp_index [ 1 ] ] [ 0 ] ;
 cur_lsp [ 4 ] = lsp_band1 [ lsp_index [ 1 ] ] [ 1 ] ;
 cur_lsp [ 5 ] = lsp_band1 [ lsp_index [ 1 ] ] [ 2 ] ;
 cur_lsp [ 6 ] = lsp_band2 [ lsp_index [ 2 ] ] [ 0 ] ;
 cur_lsp [ 7 ] = lsp_band2 [ lsp_index [ 2 ] ] [ 1 ] ;
 cur_lsp [ 8 ] = lsp_band2 [ lsp_index [ 2 ] ] [ 2 ] ;
 cur_lsp [ 9 ] = lsp_band2 [ lsp_index [ 2 ] ] [ 3 ] ;
 for ( i = 0 ;
 i < LPC_ORDER ;
 i ++ ) {
 temp = ( ( prev_lsp [ i ] - dc_lsp [ i ] ) * pred + ( 1 << 14 ) ) >> 15 ;
 cur_lsp [ i ] += dc_lsp [ i ] + temp ;
 }
 for ( i = 0 ;
 i < LPC_ORDER ;
 i ++ ) {
 cur_lsp [ 0 ] = FFMAX ( cur_lsp [ 0 ] , 0x180 ) ;
 cur_lsp [ LPC_ORDER - 1 ] = FFMIN ( cur_lsp [ LPC_ORDER - 1 ] , 0x7e00 ) ;
 for ( j = 1 ;
 j < LPC_ORDER ;
 j ++ ) {
 temp = min_dist + cur_lsp [ j - 1 ] - cur_lsp [ j ] ;
 if ( temp > 0 ) {
 temp >>= 1 ;
 cur_lsp [ j - 1 ] -= temp ;
 cur_lsp [ j ] += temp ;
 }
 }
 stable = 1 ;
 for ( j = 1 ;
 j < LPC_ORDER ;
 j ++ ) {
 temp = cur_lsp [ j - 1 ] + min_dist - cur_lsp [ j ] - 4 ;
 if ( temp > 0 ) {
 stable = 0 ;
 break ;
 }
 }
 if ( stable ) break ;
 }
 if ( ! stable ) memcpy ( cur_lsp , prev_lsp , LPC_ORDER * sizeof ( * cur_lsp ) ) ;
 }