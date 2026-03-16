static void y4m_convert_411_420jpeg ( y4m_input * _y4m , unsigned char * _dst , unsigned char * _aux ) {
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
 x < OC_MINI ( c_w , 1 ) ;
 x ++ ) {
 tmp [ x << 1 ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 111 * _aux [ 0 ] + 18 * _aux [ OC_MINI ( 1 , c_w - 1 ) ] - _aux [ OC_MINI ( 2 , c_w - 1 ) ] + 64 ) >> 7 , 255 ) ;
 tmp [ x << 1 | 1 ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 47 * _aux [ 0 ] + 86 * _aux [ OC_MINI ( 1 , c_w - 1 ) ] - 5 * _aux [ OC_MINI ( 2 , c_w - 1 ) ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 x < c_w - 2 ;
 x ++ ) {
 tmp [ x << 1 ] = ( unsigned char ) OC_CLAMPI ( 0 , ( _aux [ x - 1 ] + 110 * _aux [ x ] + 18 * _aux [ x + 1 ] - _aux [ x + 2 ] + 64 ) >> 7 , 255 ) ;
 tmp [ x << 1 | 1 ] = ( unsigned char ) OC_CLAMPI ( 0 , ( - 3 * _aux [ x - 1 ] + 50 * _aux [ x ] + 86 * _aux [ x + 1 ] - 5 * _aux [ x + 2 ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 x < c_w ;
 x ++ ) {
 tmp [ x << 1 ] = ( unsigned char ) OC_CLAMPI ( 0 , ( _aux [ x - 1 ] + 110 * _aux [ x ] + 18 * _aux [ OC_MINI ( x + 1 , c_w - 1 ) ] - _aux [ c_w - 1 ] + 64 ) >> 7 , 255 ) ;
 if ( ( x << 1 | 1 ) < dst_c_w ) {
 tmp [ x << 1 | 1 ] = ( unsigned char ) OC_CLAMPI ( 0 , ( - 3 * _aux [ x - 1 ] + 50 * _aux [ x ] + 86 * _aux [ OC_MINI ( x + 1 , c_w - 1 ) ] - 5 * _aux [ c_w - 1 ] + 64 ) >> 7 , 255 ) ;
 }
 }
 tmp += dst_c_w ;
 _aux += c_w ;
 }
 tmp -= tmp_sz ;
 y4m_422jpeg_420jpeg_helper ( _dst , tmp , dst_c_w , c_h ) ;
 _dst += dst_c_sz ;
 }
 }