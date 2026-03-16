void vp8_subtract_mby_c ( short * diff , unsigned char * src , int src_stride , unsigned char * pred , int pred_stride ) {
 int r , c ;
 for ( r = 0 ;
 r < 16 ;
 r ++ ) {
 for ( c = 0 ;
 c < 16 ;
 c ++ ) {
 diff [ c ] = src [ c ] - pred [ c ] ;
 }
 diff += 16 ;
 pred += pred_stride ;
 src += src_stride ;
 }
 }