static vpx_image_t * encoder_get_preview ( vpx_codec_alg_priv_t * ctx ) {
 YV12_BUFFER_CONFIG sd ;
 vp9_ppflags_t flags ;
 vp9_zero ( flags ) ;
 if ( ctx -> preview_ppcfg . post_proc_flag ) {
 flags . post_proc_flag = ctx -> preview_ppcfg . post_proc_flag ;
 flags . deblocking_level = ctx -> preview_ppcfg . deblocking_level ;
 flags . noise_level = ctx -> preview_ppcfg . noise_level ;
 }
 if ( vp9_get_preview_raw_frame ( ctx -> cpi , & sd , & flags ) == 0 ) {
 yuvconfig2image ( & ctx -> preview_img , & sd , NULL ) ;
 return & ctx -> preview_img ;
 }
 else {
 return NULL ;
 }
 }