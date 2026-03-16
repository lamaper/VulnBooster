static void mp_flush ( MPADecodeContext * ctx ) {
 memset ( ctx -> synth_buf , 0 , sizeof ( ctx -> synth_buf ) ) ;
 ctx -> last_buf_size = 0 ;
 }