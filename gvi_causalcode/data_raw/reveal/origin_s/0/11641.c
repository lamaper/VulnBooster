static void imc_decode_level_coefficients ( IMCContext * q , int * levlCoeffBuf , float * flcoeffs1 , float * flcoeffs2 ) {
 int i , level ;
 float tmp , tmp2 ;
 flcoeffs1 [ 0 ] = 20000.0 / pow ( 2 , levlCoeffBuf [ 0 ] * 0.18945 ) ;
 flcoeffs2 [ 0 ] = log2f ( flcoeffs1 [ 0 ] ) ;
 tmp = flcoeffs1 [ 0 ] ;
 tmp2 = flcoeffs2 [ 0 ] ;
 for ( i = 1 ;
 i < BANDS ;
 i ++ ) {
 level = levlCoeffBuf [ i ] ;
 if ( level == 16 ) {
 flcoeffs1 [ i ] = 1.0 ;
 flcoeffs2 [ i ] = 0.0 ;
 }
 else {
 if ( level < 17 ) level -= 7 ;
 else if ( level <= 24 ) level -= 32 ;
 else level -= 16 ;
 tmp *= imc_exp_tab [ 15 + level ] ;
 tmp2 += 0.83048 * level ;
 flcoeffs1 [ i ] = tmp ;
 flcoeffs2 [ i ] = tmp2 ;
 }
 }
 }