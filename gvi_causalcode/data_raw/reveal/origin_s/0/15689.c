static int s_aos_seek ( register stream * s , gs_offset_t pos ) {
 uint end = s -> srlimit - s -> cbuf + 1 ;
 long offset = pos - s -> position ;
 if ( offset >= 0 && offset <= end ) {
 s -> srptr = s -> cbuf + offset - 1 ;
 return 0 ;
 }
 if ( pos < 0 || pos > s -> file_limit ) return ERRC ;
 s -> srptr = s -> srlimit = s -> cbuf - 1 ;
 s -> end_status = 0 ;
 s -> position = pos ;
 return 0 ;
 }