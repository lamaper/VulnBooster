static vpx_codec_err_t encoder_init ( vpx_codec_ctx_t * ctx , vpx_codec_priv_enc_mr_cfg_t * data ) {
 vpx_codec_err_t res = VPX_CODEC_OK ;
 ( void ) data ;
 if ( ctx -> priv == NULL ) {
 vpx_codec_alg_priv_t * const priv = vpx_calloc ( 1 , sizeof ( * priv ) ) ;
 if ( priv == NULL ) return VPX_CODEC_MEM_ERROR ;
 ctx -> priv = ( vpx_codec_priv_t * ) priv ;
 ctx -> priv -> init_flags = ctx -> init_flags ;
 ctx -> priv -> enc . total_encoders = 1 ;
 if ( ctx -> config . enc ) {
 priv -> cfg = * ctx -> config . enc ;
 ctx -> config . enc = & priv -> cfg ;
 }
 priv -> extra_cfg = default_extra_cfg ;
 vp9_initialize_enc ( ) ;
 res = validate_config ( priv , & priv -> cfg , & priv -> extra_cfg ) ;
 if ( res == VPX_CODEC_OK ) {
 set_encoder_config ( & priv -> oxcf , & priv -> cfg , & priv -> extra_cfg ) ;
 priv -> cpi = vp9_create_compressor ( & priv -> oxcf ) ;
 if ( priv -> cpi == NULL ) res = VPX_CODEC_MEM_ERROR ;
 else priv -> cpi -> output_pkt_list = & priv -> pkt_list . head ;
 }
 }
 return res ;
 }