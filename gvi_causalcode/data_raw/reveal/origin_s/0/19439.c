static int amr_decode_fix_avctx ( AVCodecContext * avctx ) {
 const int is_amr_wb = 1 + ( avctx -> codec_id == AV_CODEC_ID_AMR_WB ) ;
 avctx -> sample_rate = 8000 * is_amr_wb ;
 if ( avctx -> channels > 1 ) {
 av_log_missing_feature ( avctx , "multi-channel AMR" , 0 ) ;
 return AVERROR_PATCHWELCOME ;
 }
 avctx -> channels = 1 ;
 avctx -> channel_layout = AV_CH_LAYOUT_MONO ;
 avctx -> sample_fmt = AV_SAMPLE_FMT_S16 ;
 return 0 ;
 }