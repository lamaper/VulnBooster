void vp8_subtract_mbuv_c ( short * diff , unsigned char * usrc , unsigned char * vsrc , int src_stride , unsigned char * upred , unsigned char * vpred , int pred_stride ) {
 short * udiff = diff + 256 ;
 short * vdiff = diff + 320 ;
 int r , c ;
 for ( r = 0 ;
 r < 8 ;
 r ++ ) {
 for ( c = 0 ;
 c < 8 ;
 c ++ ) {
 udiff [ c ] = usrc [ c ] - upred [ c ] ;
 }
 udiff += 8 ;
 upred += pred_stride ;
 usrc += src_stride ;
 }
 for ( r = 0 ;
 r < 8 ;
 r ++ ) {
 for ( c = 0 ;
 c < 8 ;
 c ++ ) {
 vdiff [ c ] = vsrc [ c ] - vpred [ c ] ;
 }
 vdiff += 8 ;
 vpred += pred_stride ;
 vsrc += src_stride ;
 }
 }