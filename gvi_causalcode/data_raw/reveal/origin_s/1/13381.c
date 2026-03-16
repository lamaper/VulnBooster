struct mszipd_stream * mszipd_init ( struct mspack_system * system , struct mspack_file * input , struct mspack_file * output , int input_buffer_size , int repair_mode ) {
 struct mszipd_stream * zip ;
 if ( ! system ) return NULL ;
 input_buffer_size = ( input_buffer_size + 1 ) & - 2 ;
 if ( ! input_buffer_size ) return NULL ;
 if ( ! ( zip = ( struct mszipd_stream * ) system -> alloc ( system , sizeof ( struct mszipd_stream ) ) ) ) {
 return NULL ;
 }
 zip -> inbuf = ( unsigned char * ) system -> alloc ( system , ( size_t ) input_buffer_size ) ;
 if ( ! zip -> inbuf ) {
 system -> free ( zip ) ;
 return NULL ;
 }
 zip -> sys = system ;
 zip -> input = input ;
 zip -> output = output ;
 zip -> inbuf_size = input_buffer_size ;
 zip -> input_end = 0 ;
 zip -> error = MSPACK_ERR_OK ;
 zip -> repair_mode = repair_mode ;
 zip -> flush_window = & mszipd_flush_window ;
 zip -> i_ptr = zip -> i_end = & zip -> inbuf [ 0 ] ;
 zip -> o_ptr = zip -> o_end = NULL ;
 zip -> bit_buffer = 0 ;
 zip -> bits_left = 0 ;
 return zip ;
 }