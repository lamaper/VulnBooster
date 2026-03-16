void evsignal_dealloc ( struct event_base * base ) {
 int i = 0 ;
 if ( base -> sig . ev_signal_added ) {
 event_del ( & base -> sig . ev_signal ) ;
 base -> sig . ev_signal_added = 0 ;
 }
 for ( i = 0 ;
 i < NSIG ;
 ++ i ) {
 if ( i < base -> sig . sh_old_max && base -> sig . sh_old [ i ] != NULL ) _evsignal_restore_handler ( base , i ) ;
 }
 EVUTIL_CLOSESOCKET ( base -> sig . ev_signal_pair [ 0 ] ) ;
 base -> sig . ev_signal_pair [ 0 ] = - 1 ;
 EVUTIL_CLOSESOCKET ( base -> sig . ev_signal_pair [ 1 ] ) ;
 base -> sig . ev_signal_pair [ 1 ] = - 1 ;
 base -> sig . sh_old_max = 0 ;
 free ( base -> sig . sh_old ) ;
 }