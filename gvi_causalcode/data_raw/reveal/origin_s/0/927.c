TSHttpParser TSHttpParserCreate ( void ) {
 TSHttpParser parser = reinterpret_cast < TSHttpParser > ( ats_malloc ( sizeof ( HTTPParser ) ) ) ;
 http_parser_init ( ( HTTPParser * ) parser ) ;
 return parser ;
 }