static int s_aos_close ( stream * s ) {
 gs_free_object ( s -> memory , s -> cbuf , "s_aos_close(buffer)" ) ;
 s -> cbuf = 0 ;
 s -> read_id = s -> write_id = ( s -> read_id | s -> write_id ) + 1 ;
 return 0 ;
 }