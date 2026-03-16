static void update_image_md5 ( const vpx_image_t * img , const int planes [ 3 ] , MD5Context * md5 ) {
 int i , y ;
 for ( i = 0 ;
 i < 3 ;
 ++ i ) {
 const int plane = planes [ i ] ;
 const unsigned char * buf = img -> planes [ plane ] ;
 const int stride = img -> stride [ plane ] ;
 const int w = vpx_img_plane_width ( img , plane ) ;
 const int h = vpx_img_plane_height ( img , plane ) ;
 for ( y = 0 ;
 y < h ;
 ++ y ) {
 MD5Update ( md5 , buf , w ) ;
 buf += stride ;
 }
 }
 }