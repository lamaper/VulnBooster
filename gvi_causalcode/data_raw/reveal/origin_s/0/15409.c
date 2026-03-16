static void y4m_422jpeg_420jpeg_helper ( unsigned char * _dst , const unsigned char * _src , int _c_w , int _c_h ) {
 int y ;
 int x ;
 for ( x = 0 ;
 x < _c_w ;
 x ++ ) {
 for ( y = 0 ;
 y < OC_MINI ( _c_h , 2 ) ;
 y += 2 ) {
 _dst [ ( y >> 1 ) * _c_w ] = OC_CLAMPI ( 0 , ( 64 * _src [ 0 ] + 78 * _src [ OC_MINI ( 1 , _c_h - 1 ) * _c_w ] - 17 * _src [ OC_MINI ( 2 , _c_h - 1 ) * _c_w ] + 3 * _src [ OC_MINI ( 3 , _c_h - 1 ) * _c_w ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 y < _c_h - 3 ;
 y += 2 ) {
 _dst [ ( y >> 1 ) * _c_w ] = OC_CLAMPI ( 0 , ( 3 * ( _src [ ( y - 2 ) * _c_w ] + _src [ ( y + 3 ) * _c_w ] ) - 17 * ( _src [ ( y - 1 ) * _c_w ] + _src [ ( y + 2 ) * _c_w ] ) + 78 * ( _src [ y * _c_w ] + _src [ ( y + 1 ) * _c_w ] ) + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 y < _c_h ;
 y += 2 ) {
 _dst [ ( y >> 1 ) * _c_w ] = OC_CLAMPI ( 0 , ( 3 * ( _src [ ( y - 2 ) * _c_w ] + _src [ ( _c_h - 1 ) * _c_w ] ) - 17 * ( _src [ ( y - 1 ) * _c_w ] + _src [ OC_MINI ( y + 2 , _c_h - 1 ) * _c_w ] ) + 78 * ( _src [ y * _c_w ] + _src [ OC_MINI ( y + 1 , _c_h - 1 ) * _c_w ] ) + 64 ) >> 7 , 255 ) ;
 }
 _src ++ ;
 _dst ++ ;
 }
 }