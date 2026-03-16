int vp9_get_y_sse ( const YV12_BUFFER_CONFIG * a , const YV12_BUFFER_CONFIG * b ) {
 assert ( a -> y_crop_width == b -> y_crop_width ) ;
 assert ( a -> y_crop_height == b -> y_crop_height ) ;
 return ( int ) get_sse ( a -> y_buffer , a -> y_stride , b -> y_buffer , b -> y_stride , a -> y_crop_width , a -> y_crop_height ) ;
 }