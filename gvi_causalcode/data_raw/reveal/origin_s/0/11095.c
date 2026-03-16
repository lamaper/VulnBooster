int make_rss ( i_ctx_t * i_ctx_p , os_ptr op , const byte * data , uint size , uint string_space , long offset , long length , bool is_bytestring ) {
 uint save_space = icurrent_space ;
 stream * s ;
 long left = min ( length , size - offset ) ;
 ialloc_set_space ( idmemory , string_space ) ;
 s = file_alloc_stream ( imemory , "make_rss" ) ;
 ialloc_set_space ( idmemory , save_space ) ;
 if ( s == 0 ) return_error ( gs_error_VMerror ) ;
 sread_string_reusable ( s , data + offset , max ( left , 0 ) ) ;
 if ( is_bytestring ) s -> cbuf_string . data = 0 ;
 make_stream_file ( op , s , "r" ) ;
 return 0 ;
 }