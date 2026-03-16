static int mpeg_decode_postinit ( AVCodecContext * avctx ) {
 Mpeg1Context * s1 = avctx -> priv_data ;
 MpegEncContext * s = & s1 -> mpeg_enc_ctx ;
 uint8_t old_permutation [ 64 ] ;
 if ( ( s1 -> mpeg_enc_ctx_allocated == 0 ) || avctx -> coded_width != s -> width || avctx -> coded_height != s -> height || s1 -> save_width != s -> width || s1 -> save_height != s -> height || s1 -> save_aspect_info != s -> aspect_ratio_info || s1 -> save_progressive_seq != s -> progressive_sequence || 0 ) {
 if ( s1 -> mpeg_enc_ctx_allocated ) {
 ParseContext pc = s -> parse_context ;
 s -> parse_context . buffer = 0 ;
 ff_MPV_common_end ( s ) ;
 s -> parse_context = pc ;
 }
 if ( ( s -> width == 0 ) || ( s -> height == 0 ) ) return - 2 ;
 avcodec_set_dimensions ( avctx , s -> width , s -> height ) ;
 avctx -> bit_rate = s -> bit_rate ;
 s1 -> save_aspect_info = s -> aspect_ratio_info ;
 s1 -> save_width = s -> width ;
 s1 -> save_height = s -> height ;
 s1 -> save_progressive_seq = s -> progressive_sequence ;
 avctx -> has_b_frames = ! s -> low_delay ;
 if ( avctx -> codec_id == AV_CODEC_ID_MPEG1VIDEO ) {
 avctx -> time_base . den = ff_mpeg12_frame_rate_tab [ s -> frame_rate_index ] . num ;
 avctx -> time_base . num = ff_mpeg12_frame_rate_tab [ s -> frame_rate_index ] . den ;
 avctx -> sample_aspect_ratio = av_d2q ( 1.0 / ff_mpeg1_aspect [ s -> aspect_ratio_info ] , 255 ) ;
 avctx -> ticks_per_frame = 1 ;
 }
 else {
 av_reduce ( & s -> avctx -> time_base . den , & s -> avctx -> time_base . num , ff_mpeg12_frame_rate_tab [ s -> frame_rate_index ] . num * s1 -> frame_rate_ext . num * 2 , ff_mpeg12_frame_rate_tab [ s -> frame_rate_index ] . den * s1 -> frame_rate_ext . den , 1 << 30 ) ;
 avctx -> ticks_per_frame = 2 ;
 if ( s -> aspect_ratio_info > 1 ) {
 AVRational dar = av_mul_q ( av_div_q ( ff_mpeg2_aspect [ s -> aspect_ratio_info ] , ( AVRational ) {
 s1 -> pan_scan . width , s1 -> pan_scan . height }
 ) , ( AVRational ) {
 s -> width , s -> height }
 ) ;
 if ( ( s1 -> pan_scan . width == 0 ) || ( s1 -> pan_scan . height == 0 ) || ( av_cmp_q ( dar , ( AVRational ) {
 4 , 3 }
 ) && av_cmp_q ( dar , ( AVRational ) {
 16 , 9 }
 ) ) ) {
 s -> avctx -> sample_aspect_ratio = av_div_q ( ff_mpeg2_aspect [ s -> aspect_ratio_info ] , ( AVRational ) {
 s -> width , s -> height }
 ) ;
 }
 else {
 s -> avctx -> sample_aspect_ratio = av_div_q ( ff_mpeg2_aspect [ s -> aspect_ratio_info ] , ( AVRational ) {
 s1 -> pan_scan . width , s1 -> pan_scan . height }
 ) ;
 av_dlog ( avctx , "A %d/%d\n" , ff_mpeg2_aspect [ s -> aspect_ratio_info ] . num , ff_mpeg2_aspect [ s -> aspect_ratio_info ] . den ) ;
 av_dlog ( avctx , "B %d/%d\n" , s -> avctx -> sample_aspect_ratio . num , s -> avctx -> sample_aspect_ratio . den ) ;
 }
 }
 else {
 s -> avctx -> sample_aspect_ratio = ff_mpeg2_aspect [ s -> aspect_ratio_info ] ;
 }
 }
 avctx -> pix_fmt = mpeg_get_pixelformat ( avctx ) ;
 avctx -> hwaccel = ff_find_hwaccel ( avctx -> codec -> id , avctx -> pix_fmt ) ;
 if ( avctx -> pix_fmt == AV_PIX_FMT_XVMC_MPEG2_IDCT || avctx -> hwaccel || s -> avctx -> codec -> capabilities & CODEC_CAP_HWACCEL_VDPAU ) if ( avctx -> idct_algo == FF_IDCT_AUTO ) avctx -> idct_algo = FF_IDCT_SIMPLE ;
 memcpy ( old_permutation , s -> dsp . idct_permutation , 64 * sizeof ( uint8_t ) ) ;
 if ( ff_MPV_common_init ( s ) < 0 ) return - 2 ;
 quant_matrix_rebuild ( s -> intra_matrix , old_permutation , s -> dsp . idct_permutation ) ;
 quant_matrix_rebuild ( s -> inter_matrix , old_permutation , s -> dsp . idct_permutation ) ;
 quant_matrix_rebuild ( s -> chroma_intra_matrix , old_permutation , s -> dsp . idct_permutation ) ;
 quant_matrix_rebuild ( s -> chroma_inter_matrix , old_permutation , s -> dsp . idct_permutation ) ;
 s1 -> mpeg_enc_ctx_allocated = 1 ;
 }
 return 0 ;
 }