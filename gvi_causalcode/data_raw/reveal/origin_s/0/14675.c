static int equal_dimensions ( const YV12_BUFFER_CONFIG * a , const YV12_BUFFER_CONFIG * b ) {
 return a -> y_height == b -> y_height && a -> y_width == b -> y_width && a -> uv_height == b -> uv_height && a -> uv_width == b -> uv_width ;
 }