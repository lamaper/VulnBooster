const char * TSMatcherParseSrcIPConfigLine ( char * line , TSMatcherLine ml ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) line ) == TS_SUCCESS ) ;
 return parseConfigLine ( line , ( matcher_line * ) ml , & ip_allow_src_tags ) ;
 }