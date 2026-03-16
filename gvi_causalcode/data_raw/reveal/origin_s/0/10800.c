static inline void get_grantor ( THD * thd , char * grantor ) {
 const char * user = thd -> security_ctx -> user ;
 const char * host = thd -> security_ctx -> host_or_ip ;

 user = thd -> get_invoker_user ( ) . str ;
 host = thd -> get_invoker_host ( ) . str ;
 }

 }