int cache_handler ( TSCont contp , TSEvent event , void * data ) {
 Debug ( "sdk_ut_cache_write" , "Event %d data %p" , event , data ) ;
 CacheVConnStruct * cache_vconn = ( CacheVConnStruct * ) TSContDataGet ( contp ) ;
 TSIOBufferBlock blockp ;
 char * ptr_block ;
 int64_t ntodo , ndone , nbytes , towrite , avail , content_length ;
 switch ( event ) {
 case TS_EVENT_CACHE_OPEN_WRITE : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_CACHE_OPEN_WRITE %d %p" , event , data ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSCacheWrite" , "TestCase1" , TC_PASS , "ok" ) ;
 cache_vconn -> write_vconnp = ( TSVConn ) data ;
 cache_vconn -> bufp = TSIOBufferCreate ( ) ;
 cache_vconn -> readerp = TSIOBufferReaderAlloc ( cache_vconn -> bufp ) ;
 cache_vconn -> out_bufp = TSIOBufferCreate ( ) ;
 cache_vconn -> out_readerp = TSIOBufferReaderAlloc ( cache_vconn -> out_bufp ) ;
 ntodo = OBJECT_SIZE ;
 ndone = 0 ;
 while ( ntodo > 0 ) {
 blockp = TSIOBufferStart ( cache_vconn -> bufp ) ;
 ptr_block = TSIOBufferBlockWriteStart ( blockp , & avail ) ;
 towrite = ( ( ntodo < avail ) ? ntodo : avail ) ;
 memcpy ( ptr_block , content + ndone , towrite ) ;
 TSIOBufferProduce ( cache_vconn -> bufp , towrite ) ;
 ntodo -= towrite ;
 ndone += towrite ;
 }
 cache_vconn -> write_vio = TSVConnWrite ( ( TSVConn ) data , contp , cache_vconn -> readerp , OBJECT_SIZE / 2 ) ;
 return 1 ;
 case TS_EVENT_CACHE_OPEN_WRITE_FAILED : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_CACHE_OPEN_WRITE_FAILED %d %p" , event , data ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSCacheWrite" , "TestCase1" , TC_FAIL , "can't open cache vc, edtata = %p" , data ) ;
 TSReleaseAssert ( ! "cache" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 case TS_EVENT_CACHE_OPEN_READ : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_CACHE_OPEN_READ %d %p" , event , data ) ;
 if ( read_counter == 2 ) {
 SDK_RPRINT ( SDK_Cache_test , "TSCacheRead" , "TestCase2" , TC_FAIL , "shouldn't open cache vc" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 SDK_RPRINT ( SDK_Cache_test , "TSCacheRead" , "TestCase1" , TC_PASS , "ok" ) ;
 cache_vconn -> read_vconnp = ( TSVConn ) data ;
 content_length = TSVConnCacheObjectSizeGet ( cache_vconn -> read_vconnp ) ;
 Debug ( UTDBG_TAG "_cache_read" , "In cache open read [Content-Length: %" PRId64 "]" , content_length ) ;
 if ( content_length != OBJECT_SIZE ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVConnCacheObjectSizeGet" , "TestCase1" , TC_FAIL , "cached data size is incorrect" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVConnCacheObjectSizeGet" , "TestCase1" , TC_PASS , "ok" ) ;
 cache_vconn -> read_vio = TSVConnRead ( ( TSVConn ) data , contp , cache_vconn -> out_bufp , content_length ) ;
 }
 return 1 ;
 case TS_EVENT_CACHE_OPEN_READ_FAILED : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_CACHE_OPEN_READ_FAILED %d %p" , event , data ) ;
 if ( read_counter == 1 ) {
 SDK_RPRINT ( SDK_Cache_test , "TSCacheRead" , "TestCase1" , TC_FAIL , "can't open cache vc" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 SDK_RPRINT ( SDK_Cache_test , "TSCacheRead" , "TestCase2" , TC_PASS , "ok" ) ;
 break ;
 case TS_EVENT_CACHE_REMOVE : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_CACHE_REMOVE %d %p" , event , data ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSCacheRemove" , "TestCase1" , TC_PASS , "ok" ) ;
 read_counter ++ ;
 TSCacheRead ( contp , cache_vconn -> key ) ;
 return 1 ;
 case TS_EVENT_CACHE_REMOVE_FAILED : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_CACHE_REMOVE_FAILED %d %p" , event , data ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSCacheRemove" , "TestCase1" , TC_FAIL , "can't remove cached item" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 case TS_EVENT_VCONN_WRITE_COMPLETE : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_VCONN_WRITE_COMPLETE %d %p" , event , data ) ;
 nbytes = TSVIONBytesGet ( cache_vconn -> write_vio ) ;
 ndone = TSVIONDoneGet ( cache_vconn -> write_vio ) ;
 ntodo = TSVIONTodoGet ( cache_vconn -> write_vio ) ;
 Debug ( UTDBG_TAG "_cache_write" , "Nbytes=%" PRId64 " Ndone=%" PRId64 " Ntodo=%" PRId64 "" , nbytes , ndone , ntodo ) ;
 if ( ndone == ( OBJECT_SIZE / 2 ) ) {
 TSVIONBytesSet ( cache_vconn -> write_vio , ( OBJECT_SIZE - 100 ) ) ;
 TSVIOReenable ( cache_vconn -> write_vio ) ;
 Debug ( UTDBG_TAG "_cache_write" , "Increment write_counter in write_complete [a]" ) ;
 return 1 ;
 }
 else if ( ndone == ( OBJECT_SIZE - 100 ) ) {
 TSVIONBytesSet ( cache_vconn -> write_vio , OBJECT_SIZE ) ;
 TSVIOReenable ( cache_vconn -> write_vio ) ;
 Debug ( UTDBG_TAG "_cache_write" , "Increment write_counter in write_complete [b]" ) ;
 return 1 ;
 }
 else if ( ndone == OBJECT_SIZE ) {
 Debug ( UTDBG_TAG "_cache_write" , "finishing up [c]" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIOReenable" , "TestCase2" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONBytesSet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVConnWrite" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSCacheWrite" , "TestCase1" , TC_FAIL , "Did not write expected # of bytes" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 if ( ( TSVIO ) data != cache_vconn -> write_vio ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVConnWrite" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 Debug ( UTDBG_TAG "_cache_write" , "finishing up [d]" ) ;
 if ( TSVIOBufferGet ( cache_vconn -> write_vio ) != cache_vconn -> bufp ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOBufferGet" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOBufferGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 if ( TSVIOContGet ( cache_vconn -> write_vio ) != contp ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOContGet" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOContGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 Debug ( UTDBG_TAG "_cache_write" , "finishing up [f]" ) ;
 if ( TSVIOMutexGet ( cache_vconn -> write_vio ) != TSContMutexGet ( contp ) ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOMutexGet" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOMutexGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 if ( TSVIOVConnGet ( cache_vconn -> write_vio ) != cache_vconn -> write_vconnp ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOVConnGet" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOVConnGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 Debug ( UTDBG_TAG "_cache_write" , "finishing up [g]" ) ;
 if ( TSVIOReaderGet ( cache_vconn -> write_vio ) != cache_vconn -> readerp ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOReaderGet" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIOReaderGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 TSVConnClose ( cache_vconn -> write_vconnp ) ;
 cache_vconn -> write_vconnp = nullptr ;
 Debug ( UTDBG_TAG "_cache_write" , "finishing up [h]" ) ;
 read_counter ++ ;
 TSCacheRead ( contp , cache_vconn -> key ) ;
 Debug ( UTDBG_TAG "_cache_read" , "starting read [i]" ) ;
 return 1 ;
 case TS_EVENT_VCONN_WRITE_READY : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_VCONN_WRITE_READY %d %p" , event , data ) ;
 if ( ( TSVIO ) data != cache_vconn -> write_vio ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVConnWrite" , "TestCase1" , TC_FAIL , "write_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 nbytes = TSVIONBytesGet ( cache_vconn -> write_vio ) ;
 ndone = TSVIONDoneGet ( cache_vconn -> write_vio ) ;
 ntodo = TSVIONTodoGet ( cache_vconn -> write_vio ) ;
 Debug ( UTDBG_TAG "_cache_write" , "Nbytes=%" PRId64 " Ndone=%" PRId64 " Ntodo=%" PRId64 "" , nbytes , ndone , ntodo ) ;
 TSVIOReenable ( cache_vconn -> write_vio ) ;
 return 1 ;
 case TS_EVENT_VCONN_READ_COMPLETE : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_VCONN_READ_COMPLETE %d %p" , event , data ) ;
 if ( ( TSVIO ) data != cache_vconn -> read_vio ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVConnRead" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 nbytes = TSVIONBytesGet ( cache_vconn -> read_vio ) ;
 ntodo = TSVIONTodoGet ( cache_vconn -> read_vio ) ;
 ndone = TSVIONDoneGet ( cache_vconn -> read_vio ) ;
 Debug ( UTDBG_TAG "_cache_read" , "Nbytes=%" PRId64 " Ndone=%" PRId64 " Ntodo=%" PRId64 "" , nbytes , ndone , ntodo ) ;
 if ( nbytes != ( ndone + ntodo ) ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIONBytesGet" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONTodoGet" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONDoneGet" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIONBytesGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONTodoGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONDoneGet" , "TestCase1" , TC_PASS , "ok" ) ;
 TSVIONDoneSet ( cache_vconn -> read_vio , 0 ) ;
 if ( TSVIONDoneGet ( cache_vconn -> read_vio ) != 0 ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIONDoneSet" , "TestCase1" , TC_FAIL , "fail to set" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIONDoneSet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 Debug ( UTDBG_TAG "_cache_write" , "finishing up [i]" ) ;
 TSContSchedule ( contp , 100 , TS_THREAD_POOL_DEFAULT ) ;
 }
 return 1 ;
 case TS_EVENT_VCONN_READ_READY : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_VCONN_READ_READY %d %p" , event , data ) ;
 if ( ( TSVIO ) data != cache_vconn -> read_vio ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVConnRead" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 nbytes = TSVIONBytesGet ( cache_vconn -> read_vio ) ;
 ntodo = TSVIONTodoGet ( cache_vconn -> read_vio ) ;
 ndone = TSVIONDoneGet ( cache_vconn -> read_vio ) ;
 Debug ( UTDBG_TAG "_cache_read" , "Nbytes=%" PRId64 " Ndone=%" PRId64 " Ntodo=%" PRId64 "" , nbytes , ndone , ntodo ) ;
 if ( nbytes != ( ndone + ntodo ) ) {
 SDK_RPRINT ( SDK_Cache_test , "TSVIONBytesGet" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONTodoGet" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONDoneGet" , "TestCase1" , TC_FAIL , "read_vio corrupted" ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 else {
 SDK_RPRINT ( SDK_Cache_test , "TSVIONBytesGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONTodoGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( SDK_Cache_test , "TSVIONDoneGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 nbytes = TSIOBufferReaderAvail ( cache_vconn -> out_readerp ) ;
 TSIOBufferReaderConsume ( cache_vconn -> out_readerp , nbytes ) ;
 TSDebug ( UTDBG_TAG "_cache_read" , "Consuming %" PRId64 " bytes from cache read VC" , nbytes ) ;
 TSVIOReenable ( cache_vconn -> read_vio ) ;
 Debug ( UTDBG_TAG "_cache_read" , "finishing up [j]" ) ;
 return 1 ;
 case TS_EVENT_TIMEOUT : Debug ( UTDBG_TAG "_cache_event" , "TS_EVENT_TIMEOUT %d %p" , event , data ) ;
 TSCacheRemove ( contp , cache_vconn -> key ) ;
 return 1 ;
 default : TSReleaseAssert ( ! "Test SDK_API_TSCache: unexpected event" ) ;
 }
 Debug ( UTDBG_TAG "_cache_event" , "DONE DONE DONE" ) ;
 Debug ( UTDBG_TAG "_cache_write" , "all tests passed [z]" ) ;
 TSIOBufferDestroy ( cache_vconn -> bufp ) ;
 TSIOBufferDestroy ( cache_vconn -> out_bufp ) ;
 TSCacheKeyDestroy ( cache_vconn -> key ) ;
 TSfree ( cache_vconn ) ;
 * SDK_Cache_pstatus = REGRESSION_TEST_PASSED ;
 return 1 ;
 }