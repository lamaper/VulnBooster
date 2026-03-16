static void ulti_pattern ( AVFrame * frame , int x , int y , int f0 , int f1 , int Y0 , int Y1 , int chroma ) {
 uint8_t Luma [ 16 ] ;
 int mask , i ;
 for ( mask = 0x80 , i = 0 ;
 mask ;
 mask >>= 1 , i ++ ) {
 if ( f0 & mask ) Luma [ i ] = Y1 ;
 else Luma [ i ] = Y0 ;
 }
 for ( mask = 0x80 , i = 8 ;
 mask ;
 mask >>= 1 , i ++ ) {
 if ( f1 & mask ) Luma [ i ] = Y1 ;
 else Luma [ i ] = Y0 ;
 }
 ulti_convert_yuv ( frame , x , y , Luma , chroma ) ;
 }