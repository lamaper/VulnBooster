void TSMimeParserDestroy ( TSMimeParser parser ) {
 sdk_assert ( sdk_sanity_check_mime_parser ( parser ) == TS_SUCCESS ) ;
 mime_parser_clear ( ( MIMEParser * ) parser ) ;
 ats_free ( parser ) ;
 }