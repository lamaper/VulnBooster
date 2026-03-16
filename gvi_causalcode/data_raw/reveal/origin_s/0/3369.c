static void y4m_convert_422jpeg_420jpeg ( y4m_input * _y4m , unsigned char * _dst , unsigned char * _aux ) {
 int c_w ;
 int c_h ;
 int c_sz ;
 int dst_c_w ;
 int dst_c_h ;
 int dst_c_sz ;
 int pli ;
 _dst += _y4m -> pic_w * _y4m -> pic_h ;
 c_w = ( _y4m -> pic_w + _y4m -> src_c_dec_h - 1 ) / _y4m -> src_c_dec_h ;
 c_h = _y4m -> pic_h ;
 dst_c_w = ( _y4m -> pic_w + _y4m -> dst_c_dec_h - 1 ) / _y4m -> dst_c_dec_h ;
 dst_c_h = ( _y4m -> pic_h + _y4m -> dst_c_dec_v - 1 ) / _y4m -> dst_c_dec_v ;
 c_sz = c_w * c_h ;
 dst_c_sz = dst_c_w * dst_c_h ;
 for ( pli = 1 ;
 pli < 3 ;
 pli ++ ) {
 y4m_422jpeg_420jpeg_helper ( _dst , _aux , c_w , c_h ) ;
 _aux += c_sz ;
 _dst += dst_c_sz ;
 }
 }