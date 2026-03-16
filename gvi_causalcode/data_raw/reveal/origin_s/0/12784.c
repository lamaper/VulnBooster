err_status_t srtp_create ( srtp_t * session , const srtp_policy_t * policy ) {
 err_status_t stat ;
 srtp_ctx_t * ctx ;
 if ( session == NULL ) return err_status_bad_param ;
 ctx = ( srtp_ctx_t * ) crypto_alloc ( sizeof ( srtp_ctx_t ) ) ;
 if ( ctx == NULL ) return err_status_alloc_fail ;
 * session = ctx ;
 ctx -> stream_template = NULL ;
 ctx -> stream_list = NULL ;
 ctx -> user_data = NULL ;
 while ( policy != NULL ) {
 stat = srtp_add_stream ( ctx , policy ) ;
 if ( stat ) {
 srtp_dealloc ( * session ) ;
 return stat ;
 }
 policy = policy -> next ;
 }
 return err_status_ok ;
 }