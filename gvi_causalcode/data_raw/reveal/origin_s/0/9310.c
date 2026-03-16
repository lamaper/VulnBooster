static enum AVPixelFormat mpeg_get_pixelformat ( AVCodecContext * avctx ) {
 Mpeg1Context * s1 = avctx -> priv_data ;
 MpegEncContext * s = & s1 -> mpeg_enc_ctx ;
 if ( avctx -> xvmc_acceleration ) return avctx -> get_format ( avctx , pixfmt_xvmc_mpg2_420 ) ;
 else if ( avctx -> codec -> capabilities & CODEC_CAP_HWACCEL_VDPAU ) {
 if ( avctx -> codec_id == AV_CODEC_ID_MPEG1VIDEO ) return AV_PIX_FMT_VDPAU_MPEG1 ;
 else return AV_PIX_FMT_VDPAU_MPEG2 ;
 }
 else {
 if ( s -> chroma_format < 2 ) return avctx -> get_format ( avctx , mpeg12_hwaccel_pixfmt_list_420 ) ;
 else if ( s -> chroma_format == 2 ) return AV_PIX_FMT_YUV422P ;
 else return AV_PIX_FMT_YUV444P ;
 }
 }