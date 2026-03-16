static get_contents_ret get_contents ( char * linebuf , size_t len , FILE * stream ) {
 size_t remaining_len = len ;
 char * curbuf = linebuf ;
 do {
 int curlen = ( ( remaining_len > ( size_t ) INT_MAX ) ? INT_MAX : remaining_len ) ;
 ( ( unsigned char * ) curbuf ) [ curlen - 1 ] = 0xff ;
 char * p = fgets_unlocked ( curbuf , curlen , stream ) ;
 if ( p == NULL ) return gcr_error ;
 if ( ( ( unsigned char * ) curbuf ) [ curlen - 1 ] == 0xff ) return gcr_ok ;
 remaining_len -= curlen - 1 ;
 curbuf += curlen - 1 ;
 }
 while ( remaining_len > 1 ) ;
 return gcr_overflow ;
 }