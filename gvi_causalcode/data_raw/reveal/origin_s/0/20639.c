void ff_h263_pred_acdc ( MpegEncContext * s , int16_t * block , int n ) {
 int x , y , wrap , a , c , pred_dc , scale , i ;
 int16_t * dc_val , * ac_val , * ac_val1 ;
 if ( n < 4 ) {
 x = 2 * s -> mb_x + ( n & 1 ) ;
 y = 2 * s -> mb_y + ( n >> 1 ) ;
 wrap = s -> b8_stride ;
 dc_val = s -> dc_val [ 0 ] ;
 ac_val = s -> ac_val [ 0 ] [ 0 ] ;
 scale = s -> y_dc_scale ;
 }
 else {
 x = s -> mb_x ;
 y = s -> mb_y ;
 wrap = s -> mb_stride ;
 dc_val = s -> dc_val [ n - 4 + 1 ] ;
 ac_val = s -> ac_val [ n - 4 + 1 ] [ 0 ] ;
 scale = s -> c_dc_scale ;
 }
 ac_val += ( ( y ) * wrap + ( x ) ) * 16 ;
 ac_val1 = ac_val ;
 a = dc_val [ ( x - 1 ) + ( y ) * wrap ] ;
 c = dc_val [ ( x ) + ( y - 1 ) * wrap ] ;
 if ( s -> first_slice_line && n != 3 ) {
 if ( n != 2 ) c = 1024 ;
 if ( n != 1 && s -> mb_x == s -> resync_mb_x ) a = 1024 ;
 }
 if ( s -> ac_pred ) {
 pred_dc = 1024 ;
 if ( s -> h263_aic_dir ) {
 if ( a != 1024 ) {
 ac_val -= 16 ;
 for ( i = 1 ;
 i < 8 ;
 i ++ ) {
 block [ s -> dsp . idct_permutation [ i << 3 ] ] += ac_val [ i ] ;
 }
 pred_dc = a ;
 }
 }
 else {
 if ( c != 1024 ) {
 ac_val -= 16 * wrap ;
 for ( i = 1 ;
 i < 8 ;
 i ++ ) {
 block [ s -> dsp . idct_permutation [ i ] ] += ac_val [ i + 8 ] ;
 }
 pred_dc = c ;
 }
 }
 }
 else {
 if ( a != 1024 && c != 1024 ) pred_dc = ( a + c ) >> 1 ;
 else if ( a != 1024 ) pred_dc = a ;
 else pred_dc = c ;
 }
 block [ 0 ] = block [ 0 ] * scale + pred_dc ;
 if ( block [ 0 ] < 0 ) block [ 0 ] = 0 ;
 else block [ 0 ] |= 1 ;
 dc_val [ ( x ) + ( y ) * wrap ] = block [ 0 ] ;
 for ( i = 1 ;
 i < 8 ;
 i ++ ) ac_val1 [ i ] = block [ s -> dsp . idct_permutation [ i << 3 ] ] ;
 for ( i = 1 ;
 i < 8 ;
 i ++ ) ac_val1 [ 8 + i ] = block [ s -> dsp . idct_permutation [ i ] ] ;
 }