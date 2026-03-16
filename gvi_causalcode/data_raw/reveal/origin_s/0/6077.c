TSMimeParser TSMimeParserCreate ( void ) {
 TSMimeParser parser = reinterpret_cast < TSMimeParser > ( ats_malloc ( sizeof ( MIMEParser ) ) ) ;
 mime_parser_init ( ( MIMEParser * ) parser ) ;
 return parser ;
 }