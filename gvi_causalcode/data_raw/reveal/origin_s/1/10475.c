static void read_sbr_extension ( AACContext * ac , SpectralBandReplication * sbr , GetBitContext * gb , int bs_extension_id , int * num_bits_left ) {
 switch ( bs_extension_id ) {
 case EXTENSION_ID_PS : if ( ! ac -> oc [ 1 ] . m4ac . ps ) {
 av_log ( ac -> avctx , AV_LOG_ERROR , "Parametric Stereo signaled to be not-present but was found in the bitstream.\n" ) ;
 skip_bits_long ( gb , * num_bits_left ) ;
 * num_bits_left = 0 ;
 }
 else {

 ac -> avctx -> profile = FF_PROFILE_AAC_HE_V2 ;

 skip_bits_long ( gb , * num_bits_left ) ;
 * num_bits_left = 0 ;

 break ;
 default : if ( bs_extension_id || * num_bits_left > 16 || show_bits ( gb , * num_bits_left ) ) avpriv_request_sample ( ac -> avctx , "Reserved SBR extensions" ) ;
 skip_bits_long ( gb , * num_bits_left ) ;
 * num_bits_left = 0 ;
 break ;
 }
 }