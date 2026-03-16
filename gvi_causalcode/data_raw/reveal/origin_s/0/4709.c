int _evsignal_restore_handler ( struct event_base * base , int evsignal ) {
 int ret = 0 ;
 struct evsignal_info * sig = & base -> sig ;



 sig -> sh_old [ evsignal ] = NULL ;

 event_warn ( "sigaction" ) ;
 ret = - 1 ;
 }

 event_warn ( "signal" ) ;
 ret = - 1 ;
 }

 return ret ;
 }