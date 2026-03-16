TSReturnCode TSHttpTxnConfigStringGet ( TSHttpTxn txnp , TSOverridableConfigKey conf , const char * * value , int * length ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * * ) value ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) length ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 switch ( conf ) {
 case TS_CONFIG_HTTP_RESPONSE_SERVER_STR : * value = sm -> t_state . txn_conf -> proxy_response_server_string ;
 * length = sm -> t_state . txn_conf -> proxy_response_server_string_len ;
 break ;
 case TS_CONFIG_HTTP_GLOBAL_USER_AGENT_HEADER : * value = sm -> t_state . txn_conf -> global_user_agent_header ;
 * length = sm -> t_state . txn_conf -> global_user_agent_header_size ;
 break ;
 case TS_CONFIG_BODY_FACTORY_TEMPLATE_BASE : * value = sm -> t_state . txn_conf -> body_factory_template_base ;
 * length = sm -> t_state . txn_conf -> body_factory_template_base_len ;
 break ;
 default : return TS_ERROR ;
 break ;
 }
 return TS_SUCCESS ;
 }