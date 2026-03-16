TSReturnCode TSHttpTxnConfigStringSet ( TSHttpTxn txnp , TSOverridableConfigKey conf , const char * value , int length ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 if ( length == - 1 ) {
 length = strlen ( value ) ;
 }
 HttpSM * s = ( HttpSM * ) txnp ;
 s -> t_state . setup_per_txn_configs ( ) ;
 switch ( conf ) {
 case TS_CONFIG_HTTP_RESPONSE_SERVER_STR : if ( value && length > 0 ) {
 s -> t_state . txn_conf -> proxy_response_server_string = const_cast < char * > ( value ) ;
 s -> t_state . txn_conf -> proxy_response_server_string_len = length ;
 }
 else {
 s -> t_state . txn_conf -> proxy_response_server_string = nullptr ;
 s -> t_state . txn_conf -> proxy_response_server_string_len = 0 ;
 }
 break ;
 case TS_CONFIG_HTTP_GLOBAL_USER_AGENT_HEADER : if ( value && length > 0 ) {
 s -> t_state . txn_conf -> global_user_agent_header = const_cast < char * > ( value ) ;
 s -> t_state . txn_conf -> global_user_agent_header_size = length ;
 }
 else {
 s -> t_state . txn_conf -> global_user_agent_header = nullptr ;
 s -> t_state . txn_conf -> global_user_agent_header_size = 0 ;
 }
 break ;
 case TS_CONFIG_BODY_FACTORY_TEMPLATE_BASE : if ( value && length > 0 ) {
 s -> t_state . txn_conf -> body_factory_template_base = const_cast < char * > ( value ) ;
 s -> t_state . txn_conf -> body_factory_template_base_len = length ;
 }
 else {
 s -> t_state . txn_conf -> body_factory_template_base = nullptr ;
 s -> t_state . txn_conf -> body_factory_template_base_len = 0 ;
 }
 break ;
 case TS_CONFIG_SSL_CERT_FILENAME : if ( value && length > 0 ) {
 s -> t_state . txn_conf -> client_cert_filename = const_cast < char * > ( value ) ;
 }
 break ;
 case TS_CONFIG_SSL_CERT_FILEPATH : if ( value && length > 0 ) {
 s -> t_state . txn_conf -> client_cert_filepath = const_cast < char * > ( value ) ;
 }
 default : return TS_ERROR ;
 break ;
 }
 return TS_SUCCESS ;
 }