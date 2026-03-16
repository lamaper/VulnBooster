static void comp_ppf_gains ( int lag , PPFParam * ppf , enum Rate cur_rate , int tgt_eng , int ccr , int res_eng ) {
 int pf_residual ;
 int temp1 , temp2 ;
 ppf -> index = lag ;
 temp1 = tgt_eng * res_eng >> 1 ;
 temp2 = ccr * ccr << 1 ;
 if ( temp2 > temp1 ) {
 if ( ccr >= res_eng ) {
 ppf -> opt_gain = ppf_gain_weight [ cur_rate ] ;
 }
 else {
 ppf -> opt_gain = ( ccr << 15 ) / res_eng * ppf_gain_weight [ cur_rate ] >> 15 ;
 }
 temp1 = ( tgt_eng << 15 ) + ( ccr * ppf -> opt_gain << 1 ) ;
 temp2 = ( ppf -> opt_gain * ppf -> opt_gain >> 15 ) * res_eng ;
 pf_residual = av_sat_add32 ( temp1 , temp2 + ( 1 << 15 ) ) >> 16 ;
 if ( tgt_eng >= pf_residual << 1 ) {
 temp1 = 0x7fff ;
 }
 else {
 temp1 = ( tgt_eng << 14 ) / pf_residual ;
 }
 ppf -> sc_gain = square_root ( temp1 << 16 ) ;
 }
 else {
 ppf -> opt_gain = 0 ;
 ppf -> sc_gain = 0x7fff ;
 }
 ppf -> opt_gain = av_clip_int16 ( ppf -> opt_gain * ppf -> sc_gain >> 15 ) ;
 }