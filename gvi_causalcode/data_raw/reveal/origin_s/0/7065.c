static void constrain_line ( int x_0 , int * x_1 , int y_0 , int * y_1 , int width , int height ) {
 int dx ;
 int dy ;
 if ( * x_1 > width ) {
 dx = * x_1 - x_0 ;
 dy = * y_1 - y_0 ;
 * x_1 = width ;
 if ( dx ) * y_1 = ( ( width - x_0 ) * dy ) / dx + y_0 ;
 }
 if ( * x_1 < 0 ) {
 dx = * x_1 - x_0 ;
 dy = * y_1 - y_0 ;
 * x_1 = 0 ;
 if ( dx ) * y_1 = ( ( 0 - x_0 ) * dy ) / dx + y_0 ;
 }
 if ( * y_1 > height ) {
 dx = * x_1 - x_0 ;
 dy = * y_1 - y_0 ;
 * y_1 = height ;
 if ( dy ) * x_1 = ( ( height - y_0 ) * dx ) / dy + x_0 ;
 }
 if ( * y_1 < 0 ) {
 dx = * x_1 - x_0 ;
 dy = * y_1 - y_0 ;
 * y_1 = 0 ;
 if ( dy ) * x_1 = ( ( 0 - y_0 ) * dx ) / dy + x_0 ;
 }
 }