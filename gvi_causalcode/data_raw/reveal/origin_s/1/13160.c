void vp9_init_intra_predictors ( ) {

 p [ TX_8X8 ] = vp9_ ## type ## _predictor_8x8 ;
 p [ TX_16X16 ] = vp9_ ## type ## _predictor_16x16 ;
 p [ TX_32X32 ] = vp9_ ## type ## _predictor_32x32 INIT_ALL_SIZES ( pred [ V_PRED ] , v ) ;
 INIT_ALL_SIZES ( pred [ H_PRED ] , h ) ;
 INIT_ALL_SIZES ( pred [ D207_PRED ] , d207 ) ;
 INIT_ALL_SIZES ( pred [ D45_PRED ] , d45 ) ;
 INIT_ALL_SIZES ( pred [ D63_PRED ] , d63 ) ;
 INIT_ALL_SIZES ( pred [ D117_PRED ] , d117 ) ;
 INIT_ALL_SIZES ( pred [ D135_PRED ] , d135 ) ;
 INIT_ALL_SIZES ( pred [ D153_PRED ] , d153 ) ;
 INIT_ALL_SIZES ( pred [ TM_PRED ] , tm ) ;
 INIT_ALL_SIZES ( dc_pred [ 0 ] [ 0 ] , dc_128 ) ;
 INIT_ALL_SIZES ( dc_pred [ 0 ] [ 1 ] , dc_top ) ;
 INIT_ALL_SIZES ( dc_pred [ 1 ] [ 0 ] , dc_left ) ;
 INIT_ALL_SIZES ( dc_pred [ 1 ] [ 1 ] , dc ) ;
