uint16_fract_t lut_inverse_interp16 ( uint16_t Value , uint16_t LutTable [ ] , int length , int NumZeroes , int NumPoles ) {
 int l = 1 ;
 int r = 0x10000 ;
 int x = 0 , res ;
 int cell0 , cell1 ;
 double val2 ;
 double y0 , y1 , x0 , x1 ;
 double a , b , f ;
 if ( NumZeroes == 0 && Value == 0 ) return 0 ;
 if ( NumZeroes > 1 || NumPoles > 1 ) {
 int a , b , sample ;
 if ( Value == 0 ) return 0 ;
 sample = ( length - 1 ) * ( ( double ) Value * ( 1. / 65535. ) ) ;
 if ( LutTable [ sample ] == 0xffff ) return 0xffff ;
 a = ( ( NumZeroes - 1 ) * 0xFFFF ) / ( length - 1 ) ;
 b = ( ( length - 1 - NumPoles ) * 0xFFFF ) / ( length - 1 ) ;
 l = a - 1 ;
 r = b + 1 ;
 if ( l < 1 ) l = 1 ;
 if ( r > 0x10000 ) r = 0x10000 ;
 if ( r <= l ) return 0 ;
 }
 if ( Value == 0 && NumZeroes ) {
 return 0 ;
 }
 while ( r > l ) {
 x = ( l + r ) / 2 ;
 res = ( int ) lut_interp_linear16 ( ( uint16_fract_t ) ( x - 1 ) , LutTable , length ) ;
 if ( res == Value ) {
 return ( uint16_fract_t ) ( x - 1 ) ;
 }
 if ( res > Value ) r = x - 1 ;
 else l = x + 1 ;
 }
 assert ( x >= 1 ) ;
 val2 = ( length - 1 ) * ( ( double ) ( x - 1 ) / 65535.0 ) ;
 cell0 = ( int ) floor ( val2 ) ;
 cell1 = ( int ) ceil ( val2 ) ;
 assert ( cell0 >= 0 ) ;
 assert ( cell1 >= 0 ) ;
 assert ( cell0 < length ) ;
 assert ( cell1 < length ) ;
 if ( cell0 == cell1 ) return ( uint16_fract_t ) x ;
 y0 = LutTable [ cell0 ] ;
 x0 = ( 65535.0 * cell0 ) / ( length - 1 ) ;
 y1 = LutTable [ cell1 ] ;
 x1 = ( 65535.0 * cell1 ) / ( length - 1 ) ;
 a = ( y1 - y0 ) / ( x1 - x0 ) ;
 b = y0 - a * x0 ;
 if ( fabs ( a ) < 0.01 ) return ( uint16_fract_t ) x ;
 f = ( ( Value - b ) / a ) ;
 if ( f < 0.0 ) return ( uint16_fract_t ) 0 ;
 if ( f >= 65535.0 ) return ( uint16_fract_t ) 0xFFFF ;
 return ( uint16_fract_t ) floor ( f + 0.5 ) ;
 }