static hb_bool_t lang_matches ( const char * lang_str , const char * spec ) {
 unsigned int len = strlen ( spec ) ;
 return strncmp ( lang_str , spec , len ) == 0 && ( lang_str [ len ] == '\0' || lang_str [ len ] == '-' ) ;
 }