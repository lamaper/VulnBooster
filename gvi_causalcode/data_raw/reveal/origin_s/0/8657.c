static void libgsm_flush ( AVCodecContext * avctx ) {
 LibGSMDecodeContext * s = avctx -> priv_data ;
 int one = 1 ;
 gsm_destroy ( s -> state ) ;
 s -> state = gsm_create ( ) ;
 if ( avctx -> codec_id == AV_CODEC_ID_GSM_MS ) gsm_option ( s -> state , GSM_OPT_WAV49 , & one ) ;
 }