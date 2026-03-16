void TSMimeHdrPrint ( TSMBuffer bufp , TSMLoc obj , TSIOBuffer iobufp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( ( sdk_sanity_check_mime_hdr_handle ( obj ) == TS_SUCCESS ) || ( sdk_sanity_check_http_hdr_handle ( obj ) == TS_SUCCESS ) ) ;
 sdk_assert ( sdk_sanity_check_iocore_structure ( iobufp ) == TS_SUCCESS ) ;
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 MIMEHdrImpl * mh = _hdr_mloc_to_mime_hdr_impl ( obj ) ;
 MIOBuffer * b = ( MIOBuffer * ) iobufp ;
 IOBufferBlock * blk ;
 int bufindex ;
 int tmp , dumpoffset = 0 ;
 int done ;
 do {
 blk = b -> get_current_block ( ) ;
 if ( ! blk || blk -> write_avail ( ) == 0 ) {
 b -> add_block ( ) ;
 blk = b -> get_current_block ( ) ;
 }
 bufindex = 0 ;
 tmp = dumpoffset ;
 done = mime_hdr_print ( heap , mh , blk -> end ( ) , blk -> write_avail ( ) , & bufindex , & tmp ) ;
 dumpoffset += bufindex ;
 b -> fill ( bufindex ) ;
 }
 while ( ! done ) ;
 }