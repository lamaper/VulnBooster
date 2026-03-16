int y4m_input_fetch_frame ( y4m_input * _y4m , FILE * _fin , vpx_image_t * _img ) {
 char frame [ 6 ] ;
 int pic_sz ;
 int c_w ;
 int c_h ;
 int c_sz ;
 int bytes_per_sample = _y4m -> bit_depth > 8 ? 2 : 1 ;
 if ( ! file_read ( frame , 6 , _fin ) ) return 0 ;
 if ( memcmp ( frame , "FRAME" , 5 ) ) {
 fprintf ( stderr , "Loss of framing in Y4M input data\n" ) ;
 return - 1 ;
 }
 if ( frame [ 5 ] != '\n' ) {
 char c ;
 int j ;
 for ( j = 0 ;
 j < 79 && file_read ( & c , 1 , _fin ) && c != '\n' ;
 j ++ ) {
 }
 if ( j == 79 ) {
 fprintf ( stderr , "Error parsing Y4M frame header\n" ) ;
 return - 1 ;
 }
 }
 if ( ! file_read ( _y4m -> dst_buf , _y4m -> dst_buf_read_sz , _fin ) ) {
 fprintf ( stderr , "Error reading Y4M frame data.\n" ) ;
 return - 1 ;
 }
 if ( ! file_read ( _y4m -> aux_buf , _y4m -> aux_buf_read_sz , _fin ) ) {
 fprintf ( stderr , "Error reading Y4M frame data.\n" ) ;
 return - 1 ;
 }
 ( * _y4m -> convert ) ( _y4m , _y4m -> dst_buf , _y4m -> aux_buf ) ;
 memset ( _img , 0 , sizeof ( * _img ) ) ;
 _img -> fmt = _y4m -> vpx_fmt ;
 _img -> w = _img -> d_w = _y4m -> pic_w ;
 _img -> h = _img -> d_h = _y4m -> pic_h ;
 _img -> x_chroma_shift = _y4m -> dst_c_dec_h >> 1 ;
 _img -> y_chroma_shift = _y4m -> dst_c_dec_v >> 1 ;
 _img -> bps = _y4m -> bps ;
 pic_sz = _y4m -> pic_w * _y4m -> pic_h * bytes_per_sample ;
 c_w = ( _y4m -> pic_w + _y4m -> dst_c_dec_h - 1 ) / _y4m -> dst_c_dec_h ;
 c_w *= bytes_per_sample ;
 c_h = ( _y4m -> pic_h + _y4m -> dst_c_dec_v - 1 ) / _y4m -> dst_c_dec_v ;
 c_sz = c_w * c_h ;
 _img -> stride [ VPX_PLANE_Y ] = _img -> stride [ VPX_PLANE_ALPHA ] = _y4m -> pic_w * bytes_per_sample ;
 _img -> stride [ VPX_PLANE_U ] = _img -> stride [ VPX_PLANE_V ] = c_w ;
 _img -> planes [ VPX_PLANE_Y ] = _y4m -> dst_buf ;
 _img -> planes [ VPX_PLANE_U ] = _y4m -> dst_buf + pic_sz ;
 _img -> planes [ VPX_PLANE_V ] = _y4m -> dst_buf + pic_sz + c_sz ;
 _img -> planes [ VPX_PLANE_ALPHA ] = _y4m -> dst_buf + pic_sz + 2 * c_sz ;
 return 1 ;
 }