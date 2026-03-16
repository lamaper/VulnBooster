static void add_frame_default ( AVFrame * f , const uint8_t * src , int src_stride , int linelen , int height ) {
 int i , j ;
 uint8_t * dst = f -> data [ 0 ] ;
 dst += ( height - 1 ) * f -> linesize [ 0 ] ;
 for ( i = height ;
 i ;
 i -- ) {
 for ( j = linelen ;
 j ;
 j -- ) * dst ++ += * src ++ ;
 src += src_stride - linelen ;
 dst -= f -> linesize [ 0 ] + linelen ;
 }
 }