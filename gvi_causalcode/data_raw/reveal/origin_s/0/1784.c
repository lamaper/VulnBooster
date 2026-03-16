static struct request * request_new ( int type , const char * name , int flags , evdns_callback_type callback , void * user_ptr ) {
 const char issuing_now = ( global_requests_inflight < global_max_requests_inflight ) ? 1 : 0 ;
 const int name_len = strlen ( name ) ;
 const int request_max_len = evdns_request_len ( name_len ) ;
 const u16 trans_id = issuing_now ? transaction_id_pick ( ) : 0xffff ;
 struct request * const req = ( struct request * ) malloc ( sizeof ( struct request ) + request_max_len ) ;
 int rlen ;
 ( void ) flags ;
 if ( ! req ) return NULL ;
 memset ( req , 0 , sizeof ( struct request ) ) ;
 evtimer_set ( & req -> timeout_event , evdns_request_timeout_callback , req ) ;
 req -> request = ( ( u8 * ) req ) + sizeof ( struct request ) ;
 req -> request_appended = 1 ;
 rlen = evdns_request_data_build ( name , name_len , trans_id , type , CLASS_INET , req -> request , request_max_len ) ;
 if ( rlen < 0 ) goto err1 ;
 req -> request_len = rlen ;
 req -> trans_id = trans_id ;
 req -> tx_count = 0 ;
 req -> request_type = type ;
 req -> user_pointer = user_ptr ;
 req -> user_callback = callback ;
 req -> ns = issuing_now ? nameserver_pick ( ) : NULL ;
 req -> next = req -> prev = NULL ;
 return req ;
 err1 : free ( req ) ;
 return NULL ;
 }