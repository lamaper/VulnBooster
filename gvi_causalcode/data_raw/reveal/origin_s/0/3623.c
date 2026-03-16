static void synth_block_hardcoded ( WMAVoiceContext * s , GetBitContext * gb , int block_idx , int size , const struct frame_type_desc * frame_desc , float * excitation ) {
 float gain ;
 int n , r_idx ;
 assert ( size <= MAX_FRAMESIZE ) ;
 if ( frame_desc -> fcb_type == FCB_TYPE_SILENCE ) {
 r_idx = pRNG ( s -> frame_cntr , block_idx , size ) ;
 gain = s -> silence_gain ;
 }
 else {
 r_idx = get_bits ( gb , 8 ) ;
 gain = wmavoice_gain_universal [ get_bits ( gb , 6 ) ] ;
 }
 memset ( s -> gain_pred_err , 0 , sizeof ( s -> gain_pred_err ) ) ;
 for ( n = 0 ;
 n < size ;
 n ++ ) excitation [ n ] = wmavoice_std_codebook [ r_idx + n ] * gain ;
 }