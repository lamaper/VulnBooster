TSParseResult TSMimeHdrParse ( TSMimeParser parser , TSMBuffer bufp , TSMLoc obj , const char * * start , const char * end ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) start ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) * start ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) end ) == TS_SUCCESS ) ;
 if ( ! isWriteable ( bufp ) ) {
 return TS_PARSE_ERROR ;
 }
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( obj ) ;
 return ( TSParseResult ) mime_parser_parse ( ( MIMEParser * ) parser , ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap , mh , start , end , false , false ) ;
 }