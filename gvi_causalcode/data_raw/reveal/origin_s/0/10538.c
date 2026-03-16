static char * expand_escapes ( const char * line , SERVER_REC * server , WI_ITEM_REC * item ) {
 char * ptr , * ret ;
 const char * prev ;
 int chr ;
 prev = line ;
 ret = ptr = g_malloc ( strlen ( line ) + 1 ) ;
 for ( ;
 * line != '\0' ;
 line ++ ) {
 if ( * line != '\\' ) {
 * ptr ++ = * line ;
 continue ;
 }
 line ++ ;
 if ( * line == '\0' ) {
 * ptr ++ = '\\' ;
 break ;
 }
 chr = expand_escape ( & line ) ;
 if ( chr == '\r' || chr == '\n' ) {
 if ( prev != line ) {
 char * prev_line = g_strndup ( prev , ( line - prev ) - 1 ) ;
 event_text ( prev_line , server , item ) ;
 g_free ( prev_line ) ;
 prev = line + 1 ;
 ptr = ret ;
 }
 }
 else if ( chr != - 1 ) {
 * ptr ++ = chr ;
 }
 else {
 * ptr ++ = '\\' ;
 * ptr ++ = * line ;
 }
 }
 * ptr = '\0' ;
 return ret ;
 }