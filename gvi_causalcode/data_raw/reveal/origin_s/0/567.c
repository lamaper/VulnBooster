static void y4m_convert_422_420jpeg ( y4m_input * _y4m , unsigned char * _dst , unsigned char * _aux ) {
 unsigned char * tmp ;
 int c_w ;
 int c_h ;
 int c_sz ;
 int dst_c_h ;
 int dst_c_sz ;
 int pli ;
 _dst += _y4m -> pic_w * _y4m -> pic_h ;
 c_w = ( _y4m -> pic_w + _y4m -> src_c_dec_h - 1 ) / _y4m -> src_c_dec_h ;
 c_h = _y4m -> pic_h ;
 dst_c_h = ( _y4m -> pic_h + _y4m -> dst_c_dec_v - 1 ) / _y4m -> dst_c_dec_v ;
 c_sz = c_w * c_h ;
 dst_c_sz = c_w * dst_c_h ;
 tmp = _aux + 2 * c_sz ;
 for ( pli = 1 ;
 pli < 3 ;
 pli ++ ) {
 y4m_42xmpeg2_42xjpeg_helper ( tmp , _aux , c_w , c_h ) ;
 y4m_422jpeg_420jpeg_helper ( _dst , tmp , c_w , c_h ) ;
 _aux += c_sz ;
 _dst += dst_c_sz ;
 }
 }