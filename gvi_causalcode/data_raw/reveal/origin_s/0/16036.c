static int zreusablestream ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 os_ptr source_op = op - 1 ;
 long length = max_long ;
 bool close_source ;
 int code ;
 check_type ( * op , t_boolean ) ;
 close_source = op -> value . boolval ;
 if ( r_has_type ( source_op , t_string ) ) {
 uint size = r_size ( source_op ) ;
 check_read ( * source_op ) ;
 code = make_rss ( i_ctx_p , source_op , source_op -> value . const_bytes , size , r_space ( source_op ) , 0L , size , false ) ;
 }
 else if ( r_has_type ( source_op , t_astruct ) ) {
 uint size = gs_object_size ( imemory , source_op -> value . pstruct ) ;
 if ( gs_object_type ( imemory , source_op -> value . pstruct ) != & st_bytes ) return_error ( gs_error_rangecheck ) ;
 check_read ( * source_op ) ;
 code = make_rss ( i_ctx_p , source_op , ( const byte * ) source_op -> value . pstruct , size , r_space ( source_op ) , 0L , size , true ) ;
 }
 else if ( r_has_type ( source_op , t_array ) ) {
 int i , blk_cnt , blk_sz ;
 ref * blk_ref ;
 ulong filelen = 0 ;
 check_read ( * source_op ) ;
 blk_cnt = r_size ( source_op ) ;
 blk_ref = source_op -> value . refs ;
 if ( blk_cnt > 0 ) {
 blk_sz = r_size ( blk_ref ) ;
 for ( i = 0 ;
 i < blk_cnt ;
 i ++ ) {
 int len ;
 check_read_type ( blk_ref [ i ] , t_string ) ;
 len = r_size ( & blk_ref [ i ] ) ;
 if ( len > blk_sz || ( len < blk_sz && i < blk_cnt - 1 ) ) return_error ( gs_error_rangecheck ) ;
 filelen += len ;
 }
 }
 if ( filelen == 0 ) {
 code = make_rss ( i_ctx_p , source_op , ( unsigned char * ) "" , 0 , r_space ( source_op ) , 0 , 0 , false ) ;
 }
 else {
 code = make_aos ( i_ctx_p , source_op , blk_sz , r_size ( & blk_ref [ blk_cnt - 1 ] ) , filelen ) ;
 }
 }
 else {
 long offset = 0 ;
 stream * source ;
 stream * s ;
 check_read_file ( i_ctx_p , source , source_op ) ;
 s = source ;
 rs : if ( s -> cbuf_string . data != 0 ) {
 long pos = stell ( s ) ;
 long avail = sbufavailable ( s ) + pos ;
 offset += pos ;
 code = make_rss ( i_ctx_p , source_op , s -> cbuf_string . data , s -> cbuf_string . size , imemory_space ( ( const gs_ref_memory_t * ) s -> memory ) , offset , min ( avail , length ) , false ) ;
 }
 else if ( s -> file != 0 ) {
 if ( ~ s -> modes & ( s_mode_read | s_mode_seek ) ) return_error ( gs_error_ioerror ) ;
 code = make_rfs ( i_ctx_p , source_op , s , offset + stell ( s ) , length ) ;
 }
 else if ( s -> state -> templat == & s_SFD_template ) {
 const stream_SFD_state * const sfd_state = ( const stream_SFD_state * ) s -> state ;
 if ( sfd_state -> eod . size != 0 ) return_error ( gs_error_rangecheck ) ;
 offset += sfd_state -> skip_count - sbufavailable ( s ) ;
 if ( sfd_state -> count != 0 ) {
 long left = max ( sfd_state -> count , 0 ) + sbufavailable ( s ) ;
 if ( left < length ) length = left ;
 }
 s = s -> strm ;
 goto rs ;
 }
 else return_error ( gs_error_rangecheck ) ;
 if ( close_source ) {
 stream * rs = fptr ( source_op ) ;
 rs -> strm = source ;
 rs -> close_strm = true ;
 }
 }
 if ( code >= 0 ) pop ( 1 ) ;
 return code ;
 }