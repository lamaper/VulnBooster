static int decode_subframe_lpc ( FLACContext * s , int32_t * decoded , int pred_order , int bps ) {
 int i ;
 int coeff_prec , qlevel ;
 int coeffs [ 32 ] ;
 for ( i = 0 ;
 i < pred_order ;
 i ++ ) {
 decoded [ i ] = get_sbits_long ( & s -> gb , bps ) ;
 }
 coeff_prec = get_bits ( & s -> gb , 4 ) + 1 ;
 if ( coeff_prec == 16 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "invalid coeff precision\n" ) ;
 return - 1 ;
 }
 qlevel = get_sbits ( & s -> gb , 5 ) ;
 if ( qlevel < 0 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "qlevel %d not supported, maybe buggy stream\n" , qlevel ) ;
 return - 1 ;
 }
 for ( i = 0 ;
 i < pred_order ;
 i ++ ) {
 coeffs [ pred_order - i - 1 ] = get_sbits ( & s -> gb , coeff_prec ) ;
 }
 if ( decode_residuals ( s , decoded , pred_order ) < 0 ) return - 1 ;
 s -> dsp . lpc ( decoded , coeffs , pred_order , qlevel , s -> blocksize ) ;
 return 0 ;
 }