struct qtmd_stream * qtmd_init ( struct mspack_system * system , struct mspack_file * input , struct mspack_file * output , int window_bits , int input_buffer_size ) {
 unsigned int window_size = 1 << window_bits ;
 struct qtmd_stream * qtm ;
 int i ;
 if ( ! system ) return NULL ;
 if ( window_bits < 10 || window_bits > 21 ) return NULL ;
 input_buffer_size = ( input_buffer_size + 1 ) & - 2 ;
 if ( input_buffer_size < 2 ) return NULL ;
 if ( ! ( qtm = ( struct qtmd_stream * ) system -> alloc ( system , sizeof ( struct qtmd_stream ) ) ) ) {
 return NULL ;
 }
 qtm -> window = ( unsigned char * ) system -> alloc ( system , ( size_t ) window_size ) ;
 qtm -> inbuf = ( unsigned char * ) system -> alloc ( system , ( size_t ) input_buffer_size ) ;
 if ( ! qtm -> window || ! qtm -> inbuf ) {
 system -> free ( qtm -> window ) ;
 system -> free ( qtm -> inbuf ) ;
 system -> free ( qtm ) ;
 return NULL ;
 }
 qtm -> sys = system ;
 qtm -> input = input ;
 qtm -> output = output ;
 qtm -> inbuf_size = input_buffer_size ;
 qtm -> window_size = window_size ;
 qtm -> window_posn = 0 ;
 qtm -> frame_todo = QTM_FRAME_SIZE ;
 qtm -> header_read = 0 ;
 qtm -> error = MSPACK_ERR_OK ;
 qtm -> i_ptr = qtm -> i_end = & qtm -> inbuf [ 0 ] ;
 qtm -> o_ptr = qtm -> o_end = & qtm -> window [ 0 ] ;
 qtm -> input_end = 0 ;
 qtm -> bits_left = 0 ;
 qtm -> bit_buffer = 0 ;
 i = window_bits * 2 ;
 qtmd_init_model ( & qtm -> model0 , & qtm -> m0sym [ 0 ] , 0 , 64 ) ;
 qtmd_init_model ( & qtm -> model1 , & qtm -> m1sym [ 0 ] , 64 , 64 ) ;
 qtmd_init_model ( & qtm -> model2 , & qtm -> m2sym [ 0 ] , 128 , 64 ) ;
 qtmd_init_model ( & qtm -> model3 , & qtm -> m3sym [ 0 ] , 192 , 64 ) ;
 qtmd_init_model ( & qtm -> model4 , & qtm -> m4sym [ 0 ] , 0 , ( i > 24 ) ? 24 : i ) ;
 qtmd_init_model ( & qtm -> model5 , & qtm -> m5sym [ 0 ] , 0 , ( i > 36 ) ? 36 : i ) ;
 qtmd_init_model ( & qtm -> model6 , & qtm -> m6sym [ 0 ] , 0 , i ) ;
 qtmd_init_model ( & qtm -> model6len , & qtm -> m6lsym [ 0 ] , 0 , 27 ) ;
 qtmd_init_model ( & qtm -> model7 , & qtm -> m7sym [ 0 ] , 0 , 7 ) ;
 return qtm ;
 }