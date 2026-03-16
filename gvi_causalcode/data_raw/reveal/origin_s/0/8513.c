static const char * const * config_connection_next_line ( struct config_connection * conn ) {
 const char * line ;
 line = i_stream_next_line ( conn -> input ) ;
 if ( line == NULL ) return NULL ;
 return t_strsplit_tabescaped ( line ) ;
 }