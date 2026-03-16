static void ulti_convert_yuv ( AVFrame * frame , int x , int y , uint8_t * luma , int chroma ) {
 uint8_t * y_plane , * cr_plane , * cb_plane ;
 int i ;
 y_plane = frame -> data [ 0 ] + x + y * frame -> linesize [ 0 ] ;
 cr_plane = frame -> data [ 1 ] + ( x / 4 ) + ( y / 4 ) * frame -> linesize [ 1 ] ;
 cb_plane = frame -> data [ 2 ] + ( x / 4 ) + ( y / 4 ) * frame -> linesize [ 2 ] ;
 cr_plane [ 0 ] = ulti_chromas [ chroma >> 4 ] ;
 cb_plane [ 0 ] = ulti_chromas [ chroma & 0xF ] ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 y_plane [ i & 3 ] = ulti_lumas [ luma [ i ] ] ;
 if ( ( i & 3 ) == 3 ) {
 / ext row y_plane += frame -> linesize [ 0 ] ;
 }
 }
 }