int read_frame ( struct VpxInputContext * input_ctx , vpx_image_t * img ) {
 FILE * f = input_ctx -> file ;
 y4m_input * y4m = & input_ctx -> y4m ;
 int shortread = 0 ;
 if ( input_ctx -> file_type == FILE_TYPE_Y4M ) {
 if ( y4m_input_fetch_frame ( y4m , f , img ) < 1 ) return 0 ;
 }
 else {
 shortread = read_yuv_frame ( input_ctx , img ) ;
 }
 return ! shortread ;
 }