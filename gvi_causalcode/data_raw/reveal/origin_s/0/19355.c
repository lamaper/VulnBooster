static int comp_interp_index ( G723_1_Context * p , int pitch_lag , int * exc_eng , int * scale ) {
 int offset = PITCH_MAX + 2 * SUBFRAME_LEN ;
 int16_t * buf = p -> audio + LPC_ORDER ;
 int index , ccr , tgt_eng , best_eng , temp ;
 * scale = scale_vector ( buf , p -> excitation , FRAME_LEN + PITCH_MAX ) ;
 buf += offset ;
 ccr = 0 ;
 index = autocorr_max ( buf , offset , & ccr , pitch_lag , SUBFRAME_LEN * 2 , - 1 ) ;
 ccr = av_sat_add32 ( ccr , 1 << 15 ) >> 16 ;
 tgt_eng = dot_product ( buf , buf , SUBFRAME_LEN * 2 ) ;
 * exc_eng = av_sat_add32 ( tgt_eng , 1 << 15 ) >> 16 ;
 if ( ccr <= 0 ) return 0 ;
 best_eng = dot_product ( buf - index , buf - index , SUBFRAME_LEN * 2 ) ;
 best_eng = av_sat_add32 ( best_eng , 1 << 15 ) >> 16 ;
 temp = best_eng * * exc_eng >> 3 ;
 if ( temp < ccr * ccr ) return index ;
 else return 0 ;
 }