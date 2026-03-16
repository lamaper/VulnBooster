static void qtmd_update_model ( struct qtmd_model * model ) {
 struct qtmd_modelsym tmp ;
 int i , j ;
 if ( -- model -> shiftsleft ) {
 for ( i = model -> entries - 1 ;
 i >= 0 ;
 i -- ) {
 model -> syms [ i ] . cumfreq >>= 1 ;
 if ( model -> syms [ i ] . cumfreq <= model -> syms [ i + 1 ] . cumfreq ) {
 model -> syms [ i ] . cumfreq = model -> syms [ i + 1 ] . cumfreq + 1 ;
 }
 }
 }
 else {
 model -> shiftsleft = 50 ;
 for ( i = 0 ;
 i < model -> entries ;
 i ++ ) {
 model -> syms [ i ] . cumfreq -= model -> syms [ i + 1 ] . cumfreq ;
 model -> syms [ i ] . cumfreq ++ ;
 model -> syms [ i ] . cumfreq >>= 1 ;
 }
 for ( i = 0 ;
 i < model -> entries - 1 ;
 i ++ ) {
 for ( j = i + 1 ;
 j < model -> entries ;
 j ++ ) {
 if ( model -> syms [ i ] . cumfreq < model -> syms [ j ] . cumfreq ) {
 tmp = model -> syms [ i ] ;
 model -> syms [ i ] = model -> syms [ j ] ;
 model -> syms [ j ] = tmp ;
 }
 }
 }
 for ( i = model -> entries - 1 ;
 i >= 0 ;
 i -- ) {
 model -> syms [ i ] . cumfreq += model -> syms [ i + 1 ] . cumfreq ;
 }
 }
 }