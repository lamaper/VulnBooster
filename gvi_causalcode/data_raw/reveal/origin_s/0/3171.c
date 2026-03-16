void EndVideoDec ( decoder_t * p_dec ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 post_mt ( p_sys ) ;
 if ( p_sys -> p_context -> codec ) avcodec_flush_buffers ( p_sys -> p_context ) ;
 wait_mt ( p_sys ) ;
 if ( p_sys -> p_ff_pic ) avcodec_free_frame ( & p_sys -> p_ff_pic ) ;
 if ( p_sys -> p_va ) vlc_va_Delete ( p_sys -> p_va ) ;
 vlc_sem_destroy ( & p_sys -> sem_mt ) ;
 }