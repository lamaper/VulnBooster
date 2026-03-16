static void y4m_convert_42xpaldv_42xjpeg ( y4m_input * _y4m , unsigned char * _dst , unsigned char * _aux ) {
 unsigned char * tmp ;
 int c_w ;
 int c_h ;
 int c_sz ;
 int pli ;
 int y ;
 int x ;
 _dst += _y4m -> pic_w * _y4m -> pic_h ;
 c_w = ( _y4m -> pic_w + 1 ) / 2 ;
 c_h = ( _y4m -> pic_h + _y4m -> dst_c_dec_h - 1 ) / _y4m -> dst_c_dec_h ;
 c_sz = c_w * c_h ;
 tmp = _aux + 2 * c_sz ;
 for ( pli = 1 ;
 pli < 3 ;
 pli ++ ) {
 y4m_42xmpeg2_42xjpeg_helper ( tmp , _aux , c_w , c_h ) ;
 _aux += c_sz ;
 switch ( pli ) {
 case 1 : {
 for ( x = 0 ;
 x < c_w ;
 x ++ ) {
 for ( y = 0 ;
 y < OC_MINI ( c_h , 3 ) ;
 y ++ ) {
 _dst [ y * c_w ] = ( unsigned char ) OC_CLAMPI ( 0 , ( tmp [ 0 ] - 9 * tmp [ OC_MAXI ( y - 2 , 0 ) * c_w ] + 35 * tmp [ OC_MAXI ( y - 1 , 0 ) * c_w ] + 114 * tmp [ y * c_w ] - 17 * tmp [ OC_MINI ( y + 1 , c_h - 1 ) * c_w ] + 4 * tmp [ OC_MINI ( y + 2 , c_h - 1 ) * c_w ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 y < c_h - 2 ;
 y ++ ) {
 _dst [ y * c_w ] = ( unsigned char ) OC_CLAMPI ( 0 , ( tmp [ ( y - 3 ) * c_w ] - 9 * tmp [ ( y - 2 ) * c_w ] + 35 * tmp [ ( y - 1 ) * c_w ] + 114 * tmp [ y * c_w ] - 17 * tmp [ ( y + 1 ) * c_w ] + 4 * tmp [ ( y + 2 ) * c_w ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 y < c_h ;
 y ++ ) {
 _dst [ y * c_w ] = ( unsigned char ) OC_CLAMPI ( 0 , ( tmp [ ( y - 3 ) * c_w ] - 9 * tmp [ ( y - 2 ) * c_w ] + 35 * tmp [ ( y - 1 ) * c_w ] + 114 * tmp [ y * c_w ] - 17 * tmp [ OC_MINI ( y + 1 , c_h - 1 ) * c_w ] + 4 * tmp [ ( c_h - 1 ) * c_w ] + 64 ) >> 7 , 255 ) ;
 }
 _dst ++ ;
 tmp ++ ;
 }
 _dst += c_sz - c_w ;
 tmp -= c_w ;
 }
 break ;
 case 2 : {
 for ( x = 0 ;
 x < c_w ;
 x ++ ) {
 for ( y = 0 ;
 y < OC_MINI ( c_h , 2 ) ;
 y ++ ) {
 _dst [ y * c_w ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 4 * tmp [ 0 ] - 17 * tmp [ OC_MAXI ( y - 1 , 0 ) * c_w ] + 114 * tmp [ y * c_w ] + 35 * tmp [ OC_MINI ( y + 1 , c_h - 1 ) * c_w ] - 9 * tmp [ OC_MINI ( y + 2 , c_h - 1 ) * c_w ] + tmp [ OC_MINI ( y + 3 , c_h - 1 ) * c_w ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 y < c_h - 3 ;
 y ++ ) {
 _dst [ y * c_w ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 4 * tmp [ ( y - 2 ) * c_w ] - 17 * tmp [ ( y - 1 ) * c_w ] + 114 * tmp [ y * c_w ] + 35 * tmp [ ( y + 1 ) * c_w ] - 9 * tmp [ ( y + 2 ) * c_w ] + tmp [ ( y + 3 ) * c_w ] + 64 ) >> 7 , 255 ) ;
 }
 for ( ;
 y < c_h ;
 y ++ ) {
 _dst [ y * c_w ] = ( unsigned char ) OC_CLAMPI ( 0 , ( 4 * tmp [ ( y - 2 ) * c_w ] - 17 * tmp [ ( y - 1 ) * c_w ] + 114 * tmp [ y * c_w ] + 35 * tmp [ OC_MINI ( y + 1 , c_h - 1 ) * c_w ] - 9 * tmp [ OC_MINI ( y + 2 , c_h - 1 ) * c_w ] + tmp [ ( c_h - 1 ) * c_w ] + 64 ) >> 7 , 255 ) ;
 }
 _dst ++ ;
 tmp ++ ;
 }
 }
 break ;
 }
 }
 }