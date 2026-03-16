static int make_aos ( i_ctx_t * i_ctx_p , os_ptr op , int blk_sz , int blk_sz_last , uint file_sz ) {
 stream * s ;
 aos_state_t * ss ;
 byte * buf ;
 const int aos_buf_size = 1024 ;
 uint save_space = icurrent_space ;
 ialloc_set_space ( idmemory , r_space ( op ) ) ;
 s = s_alloc ( imemory , "aos_stream" ) ;
 ss = ( aos_state_t * ) s_alloc_state ( imemory , & st_aos_state , "st_aos_state" ) ;
 buf = gs_alloc_bytes ( imemory , aos_buf_size , "aos_stream_buf" ) ;
 if ( s == 0 || ss == 0 || buf == 0 ) {
 gs_free_object ( imemory , buf , "aos_stream_buf" ) ;
 gs_free_object ( imemory , ss , "st_aos_state" ) ;
 gs_free_object ( imemory , s , "aos_stream" ) ;
 ialloc_set_space ( idmemory , save_space ) ;
 return_error ( gs_error_VMerror ) ;
 }
 ialloc_set_space ( idmemory , save_space ) ;
 ss -> templat = & s_aos_template ;
 ss -> blocks = * op ;
 ss -> s = s ;
 ss -> blk_sz = blk_sz ;
 ss -> blk_sz_last = blk_sz_last ;
 ss -> file_sz = file_sz ;
 s_std_init ( s , buf , aos_buf_size , & s_aos_procs , s_mode_read + s_mode_seek ) ;
 s -> state = ( stream_state * ) ss ;
 s -> file_offset = 0 ;
 s -> file_limit = S_FILE_LIMIT_MAX ;
 s -> close_at_eod = false ;
 s -> read_id = 1 ;
 make_stream_file ( op , s , "r" ) ;
 return 0 ;
 }