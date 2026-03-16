static void y4m_convert_444_420jpeg ( y4m_input * _y4m , unsigned char * _dst , unsigned char * _aux ) {
 unsigned char * tmp ;
 int c_w ;
 int c_h ;
 int c_sz ;
 int dst_c_w ;
 int dst_c_h ;
 int dst_c_sz ;
 int tmp_sz ;
 int pli ;
 int y ;
 int x ;
 _dst += _y4m -> pic_w * _y4m -> pic_h ;
 c_w = ( _y4m -> pic_w + _y4m -> src_c_dec_h - 1 ) / _y4m -> src_c_dec_h ;
 c_h = _y4m -> pic_h ;
 dst_c_w = ( _y4m -> pic_w + _y4m -> dst_c_dec_h - 1 ) / _y4m -> dst_c_dec_h ;
 dst_c_h = ( _y4m -> pic_h + _y4m -> dst_c_dec_v - 1 ) / _y4m -> dst_c_dec_v ;
 c_sz = c_w * c_h ;
 dst_c_sz = dst_c_w * dst_c_h ;
 tmp_sz = dst_c_w * c_h ;
 tmp = _aux + 2 * c_sz ;
 for ( pli = 1 ;
 pli < 3 ;
 pli ++ ) {
 for ( y = 0 ;
 y < c_h ;
 y ++ ) {
 for ( x = 0 ;
 x < OC_MINI ( c_w , 2 ) ;
 x += 2 ) {
 tmp [ x >> 1 ] = OC_CLAMPI ( 0 , ( 64 * _aux [ 0 ] + 78 * _aux [ OC_MINI ( 1 , c_w - 1 ) ] - 17 * _aux [ OC_MINI ( 2 , c_w - 1 ) ] + 3 * _aux [ OC_MINI ( 3 , c_w - 1 ) ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 x < c_w - 3 ;
 x += 2 ) {
 tmp [ x >> 1 ] = OC_CLAMPI ( 0 , ( 3 * ( _aux [ x - 2 ] + _aux [ x + 3 ] ) - 17 * ( _aux [ x - 1 ] + _aux [ x + 2 ] ) + 78 * ( _aux [ x ] + _aux [ x + 1 ] ) + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 x < c_w ;
 x += 2 ) {
 tmp [ x >> 1 ] = OC_CLAMPI ( 0 , ( 3 * ( _aux [ x - 2 ] + _aux [ c_w - 1 ] ) - * ( _aux [ x - 1 ] + _aux [ OC_MINI ( x + 2 , c_w - 1 ) ] ) + * ( _aux [ x ] + _aux [ OC_MINI ( x + 1 , c_w - 1 ) ] ) + 64 ) >> 7 , 255 ) ;
 }
 tmp += dst_c_w ;
 _aux += c_w ;
 }
 tmp -= tmp_sz ;
 y4m_422jpeg_420jpeg_helper ( _dst , tmp , dst_c_w , c_h ) ;
 _dst += dst_c_sz ;
 }
 }