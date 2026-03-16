static void y4m_42xmpeg2_42xjpeg_helper ( unsigned char * _dst , const unsigned char * _src , int _c_w , int _c_h ) {
 int y ;
 int x ;
 for ( y = 0 ;
 y < _c_h ;
 y ++ ) {
 for ( x = 0 ;
 x < OC_MINI ( _c_w , 2 ) ;
 x ++ ) {
 _dst [ x ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 4 * _src [ 0 ] - 17 * _src [ OC_MAXI ( x - 1 , 0 ) ] + * _src [ x ] + 35 * _src [ OC_MINI ( x + 1 , _c_w - 1 ) ] - 9 * _src [ OC_MINI ( x + 2 , _c_w - 1 ) ] + _src [ OC_MINI ( x + 3 , _c_w - 1 ) ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 x < _c_w - 3 ;
 x ++ ) {
 _dst [ x ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 4 * _src [ x - 2 ] - 17 * _src [ x - 1 ] + * _src [ x ] + 35 * _src [ x + 1 ] - 9 * _src [ x + 2 ] + _src [ x + 3 ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 x < _c_w ;
 x ++ ) {
 _dst [ x ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 4 * _src [ x - 2 ] - 17 * _src [ x - 1 ] + * _src [ x ] + 35 * _src [ OC_MINI ( x + 1 , _c_w - 1 ) ] - 9 * _src [ OC_MINI ( x + 2 , _c_w - 1 ) ] + _src [ _c_w - 1 ] + 64 ) >> 7 , 255 ) ;
 }
 _dst += _c_w ;
 _src += _c_w ;
 }
 }