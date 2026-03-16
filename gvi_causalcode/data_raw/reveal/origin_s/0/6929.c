static void initialize_encoder ( struct stream_state * stream , struct VpxEncoderConfig * global ) {
 int i ;
 int flags = 0 ;
 flags |= global -> show_psnr ? VPX_CODEC_USE_PSNR : 0 ;
 flags |= global -> out_part ? VPX_CODEC_USE_OUTPUT_PARTITION : 0 ;


 ctx_exit_on_error ( & stream -> encoder , "Failed to initialize encoder" ) ;
 for ( i = 0 ;
 i < stream -> config . arg_ctrl_cnt ;
 i ++ ) {
 int ctrl = stream -> config . arg_ctrls [ i ] [ 0 ] ;
 int value = stream -> config . arg_ctrls [ i ] [ 1 ] ;
 if ( vpx_codec_control_ ( & stream -> encoder , ctrl , value ) ) fprintf ( stderr , "Error: Tried to set control %d = %d\n" , ctrl , value ) ;
 ctx_exit_on_error ( & stream -> encoder , "Failed to control codec" ) ;
 }

 const VpxInterface * decoder = get_vpx_decoder_by_name ( global -> codec -> name ) ;
 vpx_codec_dec_init ( & stream -> decoder , decoder -> codec_interface ( ) , NULL , 0 ) ;
 }
