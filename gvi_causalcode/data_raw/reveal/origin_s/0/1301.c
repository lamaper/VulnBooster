void TSHttpHdrPrint ( TSMBuffer bufp , TSMLoc obj , TSIOBuffer iobufp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_iocore_structure ( iobufp ) == TS_SUCCESS ) ;
 MIOBuffer * b = ( MIOBuffer * ) iobufp ;
 IOBufferBlock * blk ;
 HTTPHdr h ;
 int bufindex ;
 int tmp , dumpoffset ;
 int done ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 ink_assert ( h . m_http -> m_type == HDR_HEAP_OBJ_HTTP_HEADER ) ;
 dumpoffset = 0 ;
 do {
 blk = b -> get_current_block ( ) ;
 if ( ! blk || blk -> write_avail ( ) == 0 ) {
 b -> add_block ( ) ;
 blk = b -> get_current_block ( ) ;
 }
 bufindex = 0 ;
 tmp = dumpoffset ;
 done = h . print ( blk -> end ( ) , blk -> write_avail ( ) , & bufindex , & tmp ) ;
 dumpoffset += bufindex ;
 b -> fill ( bufindex ) ;
 }
 while ( ! done ) ;
 }