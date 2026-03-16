int vp9_denoiser_alloc ( VP9_DENOISER * denoiser , int width , int height , int ssx , int ssy , # if CONFIG_VP9_HIGHBITDEPTH int use_highbitdepth , # endif int border ) {
 int i , fail ;
 assert ( denoiser != NULL ) ;
 for ( i = 0 ;
 i < MAX_REF_FRAMES ;
 ++ i ) {
 fail = vp9_alloc_frame_buffer ( & denoiser -> running_avg_y [ i ] , width , height , ssx , ssy , # if CONFIG_VP9_HIGHBITDEPTH use_highbitdepth , # endif border ) ;
 if ( fail ) {
 vp9_denoiser_free ( denoiser ) ;
 return 1 ;
 }


 fail = vp9_alloc_frame_buffer ( & denoiser -> mc_running_avg_y , width , height , ssx , ssy , # if CONFIG_VP9_HIGHBITDEPTH use_highbitdepth , # endif border ) ;
 if ( fail ) {
 vp9_denoiser_free ( denoiser ) ;
 return 1 ;
 }


 return 0 ;
 }