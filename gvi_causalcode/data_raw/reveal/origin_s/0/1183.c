int ff_h263_pred_dc ( MpegEncContext * s , int n , int16_t * * dc_val_ptr ) {
 int x , y , wrap , a , c , pred_dc ;
 int16_t * dc_val ;
 if ( n < 4 ) {
 x = 2 * s -> mb_x + ( n & 1 ) ;
 y = 2 * s -> mb_y + ( ( n & 2 ) >> 1 ) ;
 wrap = s -> b8_stride ;
 dc_val = s -> dc_val [ 0 ] ;
 }
 else {
 x = s -> mb_x ;
 y = s -> mb_y ;
 wrap = s -> mb_stride ;
 dc_val = s -> dc_val [ n - 4 + 1 ] ;
 }
 a = dc_val [ ( x - 1 ) + ( y ) * wrap ] ;
 c = dc_val [ ( x ) + ( y - 1 ) * wrap ] ;
 if ( s -> first_slice_line && n != 3 ) {
 if ( n != 2 ) c = 1024 ;
 if ( n != 1 && s -> mb_x == s -> resync_mb_x ) a = 1024 ;
 }
 if ( a != 1024 && c != 1024 ) pred_dc = ( a + c ) >> 1 ;
 else if ( a != 1024 ) pred_dc = a ;
 else pred_dc = c ;
 * dc_val_ptr = & dc_val [ x + y * wrap ] ;
 return pred_dc ;
 }