static int make_rfs ( i_ctx_t * i_ctx_p , os_ptr op , stream * fs , long offset , long length ) {
 uint save_space = icurrent_space ;
 uint stream_space = imemory_space ( ( const gs_ref_memory_t * ) fs -> memory ) ;
 gs_const_string fname ;
 gs_parsed_file_name_t pname ;
 stream * s ;
 int code ;
 if ( sfilename ( fs , & fname ) < 0 ) return_error ( gs_error_ioerror ) ;
 code = gs_parse_file_name ( & pname , ( const char * ) fname . data , fname . size , imemory ) ;
 if ( code < 0 ) return code ;
 if ( pname . len == 0 ) return_error ( gs_error_invalidfileaccess ) ;
 if ( pname . iodev == NULL ) pname . iodev = iodev_default ( imemory ) ;
 ialloc_set_space ( idmemory , stream_space ) ;
 code = zopen_file ( i_ctx_p , & pname , "r" , & s , imemory ) ;
 ialloc_set_space ( idmemory , save_space ) ;
 if ( code < 0 ) return code ;
 if ( sread_subfile ( s , offset , length ) < 0 ) {
 sclose ( s ) ;
 return_error ( gs_error_ioerror ) ;
 }
 s -> close_at_eod = false ;
 make_stream_file ( op , s , "r" ) ;
 return 0 ;
 }