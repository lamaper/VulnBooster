void TSFetchUrl ( const char * headers , int request_len , sockaddr const * ip , TSCont contp , TSFetchWakeUpOptions callback_options , TSFetchEvent events ) {
 if ( callback_options != NO_CALLBACK ) {
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 }
 FetchSM * fetch_sm = FetchSMAllocator . alloc ( ) ;
 fetch_sm -> init ( ( Continuation * ) contp , callback_options , events , headers , request_len , ip ) ;
 fetch_sm -> httpConnect ( ) ;
 }