static void swap_yv12 ( YV12_BUFFER_CONFIG * a , YV12_BUFFER_CONFIG * b ) {
 YV12_BUFFER_CONFIG temp = * a ;
 * a = * b ;
 * b = temp ;
 }