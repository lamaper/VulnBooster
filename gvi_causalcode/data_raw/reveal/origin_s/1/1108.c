void vp8_denoiser_set_parameters ( VP8_DENOISER * denoiser , int mode ) {
 assert ( mode > 0 ) ;
 if ( mode == 1 ) {
 denoiser -> denoiser_mode = kDenoiserOnYOnly ;
 }
 else if ( mode == 2 ) {
 denoiser -> denoiser_mode = kDenoiserOnYUV ;
 }
 else if ( mode == 3 ) {
 denoiser -> denoiser_mode = kDenoiserOnYUVAggressive ;
 }
 else {
 denoiser -> denoiser_mode = kDenoiserOnAdaptive ;
 }
 if ( denoiser -> denoiser_mode != kDenoiserOnYUVAggressive ) {
 denoiser -> denoise_pars . scale_sse_thresh = 1 ;
 denoiser -> denoise_pars . scale_motion_thresh = 8 ;
 denoiser -> denoise_pars . scale_increase_filter = 0 ;
 denoiser -> denoise_pars . denoise_mv_bias = 95 ;
 denoiser -> denoise_pars . pickmode_mv_bias = 100 ;
 denoiser -> denoise_pars . qp_thresh = 0 ;
 denoiser -> denoise_pars . consec_zerolast = UINT_MAX ;
 }
 else {
 denoiser -> denoise_pars . scale_sse_thresh = 2 ;
 denoiser -> denoise_pars . scale_motion_thresh = 16 ;
 denoiser -> denoise_pars . scale_increase_filter = 1 ;
 denoiser -> denoise_pars . denoise_mv_bias = 60 ;
 denoiser -> denoise_pars . pickmode_mv_bias = 60 ;
 denoiser -> denoise_pars . qp_thresh = 100 ;
 denoiser -> denoise_pars . consec_zerolast = 10 ;
 }
 }