static void reply_callback ( struct request * const req , u32 ttl , u32 err , struct reply * reply ) {
 switch ( req -> request_type ) {
 case TYPE_A : if ( reply ) req -> user_callback ( DNS_ERR_NONE , DNS_IPv4_A , reply -> data . a . addrcount , ttl , reply -> data . a . addresses , req -> user_pointer ) ;
 else req -> user_callback ( err , 0 , 0 , 0 , NULL , req -> user_pointer ) ;
 return ;
 case TYPE_PTR : if ( reply ) {
 char * name = reply -> data . ptr . name ;
 req -> user_callback ( DNS_ERR_NONE , DNS_PTR , 1 , ttl , & name , req -> user_pointer ) ;
 }
 else {
 req -> user_callback ( err , 0 , 0 , 0 , NULL , req -> user_pointer ) ;
 }
 return ;
 case TYPE_AAAA : if ( reply ) req -> user_callback ( DNS_ERR_NONE , DNS_IPv6_AAAA , reply -> data . aaaa . addrcount , ttl , reply -> data . aaaa . addresses , req -> user_pointer ) ;
 else req -> user_callback ( err , 0 , 0 , 0 , NULL , req -> user_pointer ) ;
 return ;
 }
 assert ( 0 ) ;
 }