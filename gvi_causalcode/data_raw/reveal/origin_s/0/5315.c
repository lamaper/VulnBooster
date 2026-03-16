void cvt_unix_to_1904 ( long long time , int32 result [ 2 ] ) {
 uint32 date1970 [ 4 ] , tm [ 4 ] ;
 uint32 year [ 2 ] ;
 int i ;
 tm [ 0 ] = time & 0xffff ;
 tm [ 1 ] = ( time >> 16 ) & 0xffff ;
 tm [ 2 ] = ( time >> 32 ) & 0xffff ;
 tm [ 3 ] = ( time >> 48 ) & 0xffff ;
 memset ( date1970 , 0 , sizeof ( date1970 ) ) ;
 year [ 0 ] = ( 60 * 60 * 24 * 365L ) & 0xffff ;
 year [ 1 ] = ( 60 * 60 * 24 * 365L ) >> 16 ;
 for ( i = 1904 ;
 i < 1970 ;
 ++ i ) {
 date1970 [ 0 ] += year [ 0 ] ;
 date1970 [ 1 ] += year [ 1 ] ;
 if ( ( i & 3 ) == 0 && ( i % 100 != 0 || i % 400 == 0 ) ) date1970 [ 0 ] += 24 * 60 * 60L ;
 date1970 [ 1 ] += ( date1970 [ 0 ] >> 16 ) ;
 date1970 [ 0 ] &= 0xffff ;
 date1970 [ 2 ] += date1970 [ 1 ] >> 16 ;
 date1970 [ 1 ] &= 0xffff ;
 date1970 [ 3 ] += date1970 [ 2 ] >> 16 ;
 date1970 [ 2 ] &= 0xffff ;
 }
 for ( i = 0 ;
 i < 3 ;
 ++ i ) {
 tm [ i ] += date1970 [ i ] ;
 tm [ i + 1 ] += tm [ i ] >> 16 ;
 tm [ i ] &= 0xffff ;
 }
 tm [ 3 ] -= date1970 [ 3 ] ;
 result [ 0 ] = ( tm [ 1 ] << 16 ) | tm [ 0 ] ;
 result [ 1 ] = ( tm [ 3 ] << 16 ) | tm [ 2 ] ;
 }