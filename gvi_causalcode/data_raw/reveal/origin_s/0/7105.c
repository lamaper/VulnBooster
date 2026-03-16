static int s_aos_flush ( stream * s ) {
 s -> position = ( ( aos_state_t * ) s -> state ) -> file_sz ;
 s -> srptr = s -> srlimit = s -> cbuf - 1 ;
 return 0 ;
 }