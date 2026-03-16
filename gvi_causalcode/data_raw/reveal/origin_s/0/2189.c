void TSHttpParserClear ( TSHttpParser parser ) {
 sdk_assert ( sdk_sanity_check_http_parser ( parser ) == TS_SUCCESS ) ;
 http_parser_clear ( ( HTTPParser * ) parser ) ;
 }