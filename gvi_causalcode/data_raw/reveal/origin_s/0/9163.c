void TSUrlPrint ( TSMBuffer bufp , TSMLoc obj , TSIOBuffer iobufp ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_iocore_structure ( iobufp ) == TS_SUCCESS ) ;
 MIOBuffer * b = ( MIOBuffer * ) iobufp ;
 IOBufferBlock * blk ;
 int bufindex ;
 int tmp , dumpoffset ;
 int done ;
 URL u ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) obj ;
 dumpoffset = 0 ;
 do {
 blk = b -> get_current_block ( ) ;
 if ( ! blk || blk -> write_avail ( ) == 0 ) {
 b -> add_block ( ) ;
 blk = b -> get_current_block ( ) ;
 }
 bufindex = 0 ;
 tmp = dumpoffset ;
 done = u . print ( blk -> end ( ) , blk -> write_avail ( ) , & bufindex , & tmp ) ;
 dumpoffset += bufindex ;
 b -> fill ( bufindex ) ;
 }
 while ( ! done ) ;
 }