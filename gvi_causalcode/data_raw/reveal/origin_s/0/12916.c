static void y4m_convert_mono_420jpeg ( y4m_input * _y4m , unsigned char * _dst , unsigned char * _aux ) {
 int c_sz ;
 ( void ) _aux ;
 _dst += _y4m -> pic_w * _y4m -> pic_h ;
 c_sz = ( ( _y4m -> pic_w + _y4m -> dst_c_dec_h - 1 ) / _y4m -> dst_c_dec_h ) * ( ( _y4m -> pic_h + _y4m -> dst_c_dec_v - 1 ) / _y4m -> dst_c_dec_v ) ;
 memset ( _dst , 128 , c_sz * 2 ) ;
 }