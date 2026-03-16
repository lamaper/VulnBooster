static void s_aos_reset ( stream * s ) {
 s -> position = 0 ;
 s -> srptr = s -> srlimit = s -> cbuf - 1 ;
 s -> end_status = 0 ;
 }