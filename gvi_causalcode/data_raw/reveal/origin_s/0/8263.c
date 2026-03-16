void TSFetchPages ( TSFetchUrlParams_t * params ) {
 TSFetchUrlParams_t * myparams = params ;
 while ( myparams != nullptr ) {
 FetchSM * fetch_sm = FetchSMAllocator . alloc ( ) ;
 sockaddr * addr = ats_ip_sa_cast ( & myparams -> ip ) ;
 fetch_sm -> init ( ( Continuation * ) myparams -> contp , myparams -> options , myparams -> events , myparams -> request , myparams -> request_len , addr ) ;
 fetch_sm -> httpConnect ( ) ;
 myparams = myparams -> next ;
 }
 }