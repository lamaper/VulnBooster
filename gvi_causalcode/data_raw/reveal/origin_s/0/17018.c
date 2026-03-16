my_bool grant_init ( ) {
 THD * thd ;
 my_bool return_val ;
 DBUG_ENTER ( "grant_init" ) ;
 if ( ! ( thd = new THD ) ) DBUG_RETURN ( 1 ) ;
 thd -> thread_stack = ( char * ) & thd ;
 thd -> store_globals ( ) ;
 lex_start ( thd ) ;
 return_val = grant_reload ( thd ) ;
 delete thd ;
 my_pthread_setspecific_ptr ( THR_THD , 0 ) ;
 DBUG_RETURN ( return_val ) ;
 }