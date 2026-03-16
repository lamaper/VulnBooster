int _evsignal_set_handler ( struct event_base * base , int evsignal , void ( * handler ) ( int ) ) {



 void * p ;
 if ( evsignal >= sig -> sh_old_max ) {
 int new_max = evsignal + 1 ;
 event_debug ( ( "%s: evsignal (%d) >= sh_old_max (%d), resizing" , __func__ , evsignal , sig -> sh_old_max ) ) ;
 p = realloc ( sig -> sh_old , new_max * sizeof ( * sig -> sh_old ) ) ;
 if ( p == NULL ) {
 event_warn ( "realloc" ) ;
 return ( - 1 ) ;
 }
 memset ( ( char * ) p + sig -> sh_old_max * sizeof ( * sig -> sh_old ) , 0 , ( new_max - sig -> sh_old_max ) * sizeof ( * sig -> sh_old ) ) ;
 sig -> sh_old_max = new_max ;
 sig -> sh_old = p ;
 }
 sig -> sh_old [ evsignal ] = malloc ( sizeof * sig -> sh_old [ evsignal ] ) ;
 if ( sig -> sh_old [ evsignal ] == NULL ) {
 event_warn ( "malloc" ) ;
 return ( - 1 ) ;
 }

 sa . sa_handler = handler ;
 sa . sa_flags |= SA_RESTART ;
 sigfillset ( & sa . sa_mask ) ;
 if ( sigaction ( evsignal , & sa , sig -> sh_old [ evsignal ] ) == - 1 ) {
 event_warn ( "sigaction" ) ;
 free ( sig -> sh_old [ evsignal ] ) ;
 sig -> sh_old [ evsignal ] = NULL ;
 return ( - 1 ) ;
 }

 event_warn ( "signal" ) ;
 free ( sig -> sh_old [ evsignal ] ) ;
 sig -> sh_old [ evsignal ] = NULL ;
 return ( - 1 ) ;
 }
 * sig -> sh_old [ evsignal ] = sh ;

 }