static void libopenjpeg_copyto16 ( AVFrame * p , opj_image_t * image ) {
 int * comp_data ;
 uint16_t * img_ptr ;
 int index , x , y ;
 for ( index = 0 ;
 index < image -> numcomps ;
 index ++ ) {
 comp_data = image -> comps [ index ] . data ;
 for ( y = 0 ;
 y < image -> comps [ index ] . h ;
 y ++ ) {
 img_ptr = ( uint16_t * ) ( p -> data [ index ] + y * p -> linesize [ index ] ) ;
 for ( x = 0 ;
 x < image -> comps [ index ] . w ;
 x ++ ) {
 * img_ptr = * comp_data ;
 img_ptr ++ ;
 comp_data ++ ;
 }
 }
 }
 }