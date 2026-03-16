static void imc_calculate_coeffs ( IMCContext * q , float * flcoeffs1 , float * flcoeffs2 , int * bandWidthT , float * flcoeffs3 , float * flcoeffs5 ) {
 float workT1 [ BANDS ] ;
 float workT2 [ BANDS ] ;
 float workT3 [ BANDS ] ;
 float snr_limit = 1.e-30 ;
 float accum = 0.0 ;
 int i , cnt2 ;
 for ( i = 0 ;
 i < BANDS ;
 i ++ ) {
 flcoeffs5 [ i ] = workT2 [ i ] = 0.0 ;
 if ( bandWidthT [ i ] ) {
 workT1 [ i ] = flcoeffs1 [ i ] * flcoeffs1 [ i ] ;
 flcoeffs3 [ i ] = 2.0 * flcoeffs2 [ i ] ;
 }
 else {
 workT1 [ i ] = 0.0 ;
 flcoeffs3 [ i ] = - 30000.0 ;
 }
 workT3 [ i ] = bandWidthT [ i ] * workT1 [ i ] * 0.01 ;
 if ( workT3 [ i ] <= snr_limit ) workT3 [ i ] = 0.0 ;
 }
 for ( i = 0 ;
 i < BANDS ;
 i ++ ) {
 for ( cnt2 = i ;
 cnt2 < q -> cyclTab [ i ] ;
 cnt2 ++ ) flcoeffs5 [ cnt2 ] = flcoeffs5 [ cnt2 ] + workT3 [ i ] ;
 workT2 [ cnt2 - 1 ] = workT2 [ cnt2 - 1 ] + workT3 [ i ] ;
 }
 for ( i = 1 ;
 i < BANDS ;
 i ++ ) {
 accum = ( workT2 [ i - 1 ] + accum ) * q -> weights1 [ i - 1 ] ;
 flcoeffs5 [ i ] += accum ;
 }
 for ( i = 0 ;
 i < BANDS ;
 i ++ ) workT2 [ i ] = 0.0 ;
 for ( i = 0 ;
 i < BANDS ;
 i ++ ) {
 for ( cnt2 = i - 1 ;
 cnt2 > q -> cyclTab2 [ i ] ;
 cnt2 -- ) flcoeffs5 [ cnt2 ] += workT3 [ i ] ;
 workT2 [ cnt2 + 1 ] += workT3 [ i ] ;
 }
 accum = 0.0 ;
 for ( i = BANDS - 2 ;
 i >= 0 ;
 i -- ) {
 accum = ( workT2 [ i + 1 ] + accum ) * q -> weights2 [ i ] ;
 flcoeffs5 [ i ] += accum ;
 }
 }