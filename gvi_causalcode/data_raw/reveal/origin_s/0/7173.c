TSReturnCode TSHttpTxnConfigFind ( const char * name , int length , TSOverridableConfigKey * conf , TSRecordDataType * type ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) name ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) conf ) == TS_SUCCESS ) ;
 TSOverridableConfigKey cnf = TS_CONFIG_NULL ;
 TSRecordDataType typ = TS_RECORDDATATYPE_INT ;
 if ( length == - 1 ) {
 length = strlen ( name ) ;
 }
 switch ( length ) {
 case 24 : if ( ! strncmp ( name , "proxy.config.srv_enabled" , length ) ) {
 cnf = TS_CONFIG_SRV_ENABLED ;
 }
 break ;
 case 28 : if ( ! strncmp ( name , "proxy.config.http.cache.http" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_HTTP ;
 }
 break ;
 case 29 : if ( ! strncmp ( name , "proxy.config.ssl.hsts_max_age" , length ) ) {
 cnf = TS_CONFIG_SSL_HSTS_MAX_AGE ;
 }
 break ;
 case 31 : if ( ! strncmp ( name , "proxy.config.http.chunking.size" , length ) ) {
 cnf = TS_CONFIG_HTTP_CHUNKING_SIZE ;
 }
 break ;
 case 33 : if ( ! strncmp ( name , "proxy.config.http.cache.fuzz.time" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_FUZZ_TIME ;
 }
 else if ( ! strncmp ( name , "proxy.config.ssl.client.cert.path" , length ) ) {
 cnf = TS_CONFIG_SSL_CERT_FILEPATH ;
 typ = TS_RECORDDATATYPE_STRING ;
 }
 break ;
 case 34 : if ( ! strncmp ( name , "proxy.config.http.chunking_enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_CHUNKING_ENABLED ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.generation" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_GENERATION ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.insert_client_ip" , length ) ) {
 cnf = TS_CONFIG_HTTP_ANONYMIZE_INSERT_CLIENT_IP ;
 }
 break ;
 case 35 : switch ( name [ length - 1 ] ) {
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.range.write" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_RANGE_WRITE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.allow_multi_range" , length ) ) {
 cnf = TS_CONFIG_HTTP_ALLOW_MULTI_RANGE ;
 }
 break ;
 case 'p' : if ( ! strncmp ( name , "proxy.config.http.normalize_ae_gzip" , length ) ) {
 cnf = TS_CONFIG_HTTP_NORMALIZE_AE_GZIP ;
 }
 break ;
 }
 break ;
 case 36 : switch ( name [ length - 1 ] ) {
 case 'p' : if ( ! strncmp ( name , "proxy.config.http.cache.range.lookup" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_RANGE_LOOKUP ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.net.sock_packet_tos_out" , length ) ) {
 cnf = TS_CONFIG_NET_SOCK_PACKET_TOS_OUT ;
 }
 break ;
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.slow.log.threshold" , length ) ) {
 cnf = TS_CONFIG_HTTP_SLOW_LOG_THRESHOLD ;
 }
 break ;
 }
 break ;
 case 37 : switch ( name [ length - 1 ] ) {
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.redirection_enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_ENABLE_REDIRECTION ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.max_stale_age" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_MAX_STALE_AGE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.fuzz.min_time" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_FUZZ_MIN_TIME ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.default_buffer_size" , length ) ) {
 cnf = TS_CONFIG_HTTP_DEFAULT_BUFFER_SIZE ;
 }
 else if ( ! strncmp ( name , "proxy.config.ssl.client.cert.filename" , length ) ) {
 cnf = TS_CONFIG_SSL_CERT_FILENAME ;
 typ = TS_RECORDDATATYPE_STRING ;
 }
 break ;
 case 'r' : if ( ! strncmp ( name , "proxy.config.http.response_server_str" , length ) ) {
 cnf = TS_CONFIG_HTTP_RESPONSE_SERVER_STR ;
 typ = TS_RECORDDATATYPE_STRING ;
 }
 else if ( ! strncmp ( name , "proxy.config.ssl.client.verify.server" , length ) ) {
 cnf = TS_CONFIG_SSL_CLIENT_VERIFY_SERVER ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.http.keep_alive_post_out" , length ) ) {
 cnf = TS_CONFIG_HTTP_KEEP_ALIVE_POST_OUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.net.sock_option_flag_out" , length ) ) {
 cnf = TS_CONFIG_NET_SOCK_OPTION_FLAG_OUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.net.sock_packet_mark_out" , length ) ) {
 cnf = TS_CONFIG_NET_SOCK_PACKET_MARK_OUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.websocket.active_timeout" , length ) ) {
 cnf = TS_CONFIG_WEBSOCKET_ACTIVE_TIMEOUT ;
 }
 break ;
 }
 break ;
 case 38 : switch ( name [ length - 1 ] ) {
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.server_tcp_init_cwnd" , length ) ) {
 cnf = TS_CONFIG_HTTP_SERVER_TCP_INIT_CWND ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.flow_control.enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_FLOW_CONTROL_ENABLED ;
 }
 break ;
 break ;
 case 's' : if ( ! strncmp ( name , "proxy.config.http.send_http11_requests" , length ) ) {
 cnf = TS_CONFIG_HTTP_SEND_HTTP11_REQUESTS ;
 }
 break ;
 }
 break ;
 case 39 : switch ( name [ length - 1 ] ) {
 case 'e' : if ( ! strncmp ( name , "proxy.config.body_factory.template_base" , length ) ) {
 cnf = TS_CONFIG_BODY_FACTORY_TEMPLATE_BASE ;
 typ = TS_RECORDDATATYPE_STRING ;
 }
 break ;
 case 'm' : if ( ! strncmp ( name , "proxy.config.http.anonymize_remove_from" , length ) ) {
 cnf = TS_CONFIG_HTTP_ANONYMIZE_REMOVE_FROM ;
 }
 break ;
 case 'n' : if ( ! strncmp ( name , "proxy.config.http.keep_alive_enabled_in" , length ) ) {
 cnf = TS_CONFIG_HTTP_KEEP_ALIVE_ENABLED_IN ;
 }
 break ;
 case 's' : if ( ! strncmp ( name , "proxy.config.http.doc_in_cache_skip_dns" , length ) ) {
 cnf = TS_CONFIG_HTTP_DOC_IN_CACHE_SKIP_DNS ;
 }
 break ;
 }
 break ;
 case 40 : switch ( name [ length - 1 ] ) {
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.forward_connect_method" , length ) ) {
 cnf = TS_CONFIG_HTTP_FORWARD_CONNECT_METHOD ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.down_server.cache_time" , length ) ) {
 cnf = TS_CONFIG_HTTP_DOWN_SERVER_CACHE_TIME ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.insert_age_in_response" , length ) ) {
 cnf = TS_CONFIG_HTTP_INSERT_AGE_IN_RESPONSE ;
 }
 break ;
 case 'r' : if ( ! strncmp ( name , "proxy.config.url_remap.pristine_host_hdr" , length ) ) {
 cnf = TS_CONFIG_URL_REMAP_PRISTINE_HOST_HDR ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.insert_request_via_str" , length ) ) {
 cnf = TS_CONFIG_HTTP_INSERT_REQUEST_VIA_STR ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.flow_control.low_water" , length ) ) {
 cnf = TS_CONFIG_HTTP_FLOW_CONTROL_LOW_WATER_MARK ;
 }
 break ;
 case 's' : if ( ! strncmp ( name , "proxy.config.http.origin_max_connections" , length ) ) {
 cnf = TS_CONFIG_HTTP_ORIGIN_MAX_CONNECTIONS ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.required_headers" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_REQUIRED_HEADERS ;
 }
 else if ( ! strncmp ( name , "proxy.config.ssl.hsts_include_subdomains" , length ) ) {
 cnf = TS_CONFIG_SSL_HSTS_INCLUDE_SUBDOMAINS ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.number_of_redirections" , length ) ) {
 cnf = TS_CONFIG_HTTP_NUMBER_OF_REDIRECTIONS ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.http.keep_alive_enabled_out" , length ) ) {
 cnf = TS_CONFIG_HTTP_KEEP_ALIVE_ENABLED_OUT ;
 }
 break ;
 case 'y' : if ( ! strncmp ( name , "proxy.config.http.cache.fuzz.probability" , length ) ) {
 typ = TS_RECORDDATATYPE_FLOAT ;
 cnf = TS_CONFIG_HTTP_CACHE_FUZZ_PROBABILITY ;
 }
 break ;
 }
 break ;
 case 41 : switch ( name [ length - 1 ] ) {
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.response_server_enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_RESPONSE_SERVER_ENABLED ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.anonymize_remove_cookie" , length ) ) {
 cnf = TS_CONFIG_HTTP_ANONYMIZE_REMOVE_COOKIE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.request_header_max_size" , length ) ) {
 cnf = TS_CONFIG_HTTP_REQUEST_HEADER_MAX_SIZE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.safe_requests_retryable" , length ) ) {
 cnf = TS_CONFIG_HTTP_SAFE_REQUESTS_RETRYABLE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.parent_proxy.retry_time" , length ) ) {
 cnf = TS_CONFIG_HTTP_PARENT_PROXY_RETRY_TIME ;
 }
 break ;
 case 'r' : if ( ! strncmp ( name , "proxy.config.http.insert_response_via_str" , length ) ) {
 cnf = TS_CONFIG_HTTP_INSERT_RESPONSE_VIA_STR ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.flow_control.high_water" , length ) ) {
 cnf = TS_CONFIG_HTTP_FLOW_CONTROL_HIGH_WATER_MARK ;
 }
 break ;
 }
 break ;
 case 42 : switch ( name [ length - 1 ] ) {
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.negative_caching_enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_NEGATIVE_CACHING_ENABLED ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.when_to_revalidate" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_WHEN_TO_REVALIDATE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.response_header_max_size" , length ) ) {
 cnf = TS_CONFIG_HTTP_RESPONSE_HEADER_MAX_SIZE ;
 }
 break ;
 case 'r' : if ( ! strncmp ( name , "proxy.config.http.anonymize_remove_referer" , length ) ) {
 cnf = TS_CONFIG_HTTP_ANONYMIZE_REMOVE_REFERER ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.global_user_agent_header" , length ) ) {
 cnf = TS_CONFIG_HTTP_GLOBAL_USER_AGENT_HEADER ;
 typ = TS_RECORDDATATYPE_STRING ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.net.sock_recv_buffer_size_out" , length ) ) {
 cnf = TS_CONFIG_NET_SOCK_RECV_BUFFER_SIZE_OUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.net.sock_send_buffer_size_out" , length ) ) {
 cnf = TS_CONFIG_NET_SOCK_SEND_BUFFER_SIZE_OUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.connect_attempts_timeout" , length ) ) {
 cnf = TS_CONFIG_HTTP_CONNECT_ATTEMPTS_TIMEOUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.websocket.no_activity_timeout" , length ) ) {
 cnf = TS_CONFIG_WEBSOCKET_NO_ACTIVITY_TIMEOUT ;
 }
 break ;
 }
 break ;
 case 43 : switch ( name [ length - 1 ] ) {
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.negative_caching_lifetime" , length ) ) {
 cnf = TS_CONFIG_HTTP_NEGATIVE_CACHING_LIFETIME ;
 }
 break ;
 case 'k' : if ( ! strncmp ( name , "proxy.config.http.default_buffer_water_mark" , length ) ) {
 cnf = TS_CONFIG_HTTP_DEFAULT_BUFFER_WATER_MARK ;
 }
 break ;
 case 'l' : if ( ! strncmp ( name , "proxy.config.http.cache.cluster_cache_local" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_CLUSTER_CACHE_LOCAL ;
 }
 break ;
 case 'r' : if ( ! strncmp ( name , "proxy.config.http.cache.heuristic_lm_factor" , length ) ) {
 typ = TS_RECORDDATATYPE_FLOAT ;
 cnf = TS_CONFIG_HTTP_CACHE_HEURISTIC_LM_FACTOR ;
 }
 break ;
 }
 break ;
 case 44 : switch ( name [ length - 1 ] ) {
 case 'p' : if ( ! strncmp ( name , "proxy.config.http.anonymize_remove_client_ip" , length ) ) {
 cnf = TS_CONFIG_HTTP_ANONYMIZE_REMOVE_CLIENT_IP ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.open_read_retry_time" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_OPEN_READ_RETRY_TIME ;
 }
 break ;
 }
 break ;
 case 45 : switch ( name [ length - 1 ] ) {
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.down_server.abort_threshold" , length ) ) {
 cnf = TS_CONFIG_HTTP_DOWN_SERVER_ABORT_THRESHOLD ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.parent_proxy.fail_threshold" , length ) ) {
 cnf = TS_CONFIG_HTTP_PARENT_PROXY_FAIL_THRESHOLD ;
 }
 break ;
 case 'n' : if ( ! strncmp ( name , "proxy.config.http.cache.ignore_authentication" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_IGNORE_AUTHENTICATION ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.http.anonymize_remove_user_agent" , length ) ) {
 cnf = TS_CONFIG_HTTP_ANONYMIZE_REMOVE_USER_AGENT ;
 }
 break ;
 case 's' : if ( ! strncmp ( name , "proxy.config.http.connect_attempts_rr_retries" , length ) ) {
 cnf = TS_CONFIG_HTTP_CONNECT_ATTEMPTS_RR_RETRIES ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.max_open_read_retries" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_MAX_OPEN_READ_RETRIES ;
 }
 break ;
 case 'e' : if ( 0 == strncmp ( name , "proxy.config.http.auth_server_session_private" , length ) ) {
 cnf = TS_CONFIG_HTTP_AUTH_SERVER_SESSION_PRIVATE ;
 }
 break ;
 case 'y' : if ( ! strncmp ( name , "proxy.config.http.redirect_use_orig_cache_key" , length ) ) {
 cnf = TS_CONFIG_HTTP_REDIRECT_USE_ORIG_CACHE_KEY ;
 }
 break ;
 }
 break ;
 case 46 : switch ( name [ length - 1 ] ) {
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.ignore_client_no_cache" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_IGNORE_CLIENT_NO_CACHE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.ims_on_client_no_cache" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_IMS_ON_CLIENT_NO_CACHE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.ignore_server_no_cache" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_IGNORE_SERVER_NO_CACHE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.heuristic_min_lifetime" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_HEURISTIC_MIN_LIFETIME ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.heuristic_max_lifetime" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_HEURISTIC_MAX_LIFETIME ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.origin_max_connections_queue" , length ) ) {
 cnf = TS_CONFIG_HTTP_ORIGIN_MAX_CONNECTIONS_QUEUE ;
 }
 break ;
 case 'r' : if ( ! strncmp ( name , "proxy.config.http.insert_squid_x_forwarded_for" , length ) ) {
 cnf = TS_CONFIG_HTTP_INSERT_SQUID_X_FORWARDED_FOR ;
 }
 break ;
 case 's' : if ( ! strncmp ( name , "proxy.config.http.connect_attempts_max_retries" , length ) ) {
 cnf = TS_CONFIG_HTTP_CONNECT_ATTEMPTS_MAX_RETRIES ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.max_open_write_retries" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_MAX_OPEN_WRITE_RETRIES ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.http.forward.proxy_auth_to_parent" , length ) ) {
 cnf = TS_CONFIG_HTTP_FORWARD_PROXY_AUTH_TO_PARENT ;
 }
 break ;
 case 'h' : if ( 0 == strncmp ( name , "proxy.config.http.server_session_sharing.match" , length ) ) {
 cnf = TS_CONFIG_HTTP_SERVER_SESSION_SHARING_MATCH ;
 }
 break ;
 case 'n' : if ( ! strncmp ( name , "proxy.config.http.cache.open_write_fail_action" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_OPEN_WRITE_FAIL_ACTION ;
 }
 break ;
 }
 break ;
 case 47 : switch ( name [ length - 1 ] ) {
 case 'b' : if ( ! strncmp ( name , "proxy.config.http.parent_proxy.mark_down_hostdb" , length ) ) {
 cnf = TS_CONFIG_PARENT_FAILURES_UPDATE_HOSTDB ;
 }
 break ;
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.negative_revalidating_enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_NEGATIVE_REVALIDATING_ENABLED ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.guaranteed_min_lifetime" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_GUARANTEED_MIN_LIFETIME ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.cache.guaranteed_max_lifetime" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_GUARANTEED_MAX_LIFETIME ;
 }
 break ;
 case 'n' : if ( ! strncmp ( name , "proxy.config.http.transaction_active_timeout_in" , length ) ) {
 cnf = TS_CONFIG_HTTP_TRANSACTION_ACTIVE_TIMEOUT_IN ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.http.post_connect_attempts_timeout" , length ) ) {
 cnf = TS_CONFIG_HTTP_POST_CONNECT_ATTEMPTS_TIMEOUT ;
 }
 break ;
 }
 break ;
 case 48 : switch ( name [ length - 1 ] ) {
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.cache.ignore_client_cc_max_age" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_IGNORE_CLIENT_CC_MAX_AGE ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.negative_revalidating_lifetime" , length ) ) {
 cnf = TS_CONFIG_HTTP_NEGATIVE_REVALIDATING_LIFETIME ;
 }
 break ;
 case 't' : switch ( name [ length - 4 ] ) {
 case '_' : if ( ! strncmp ( name , "proxy.config.http.transaction_active_timeout_out" , length ) ) {
 cnf = TS_CONFIG_HTTP_TRANSACTION_ACTIVE_TIMEOUT_OUT ;
 }
 break ;
 case 'e' : if ( ! strncmp ( name , "proxy.config.http.background_fill_active_timeout" , length ) ) {
 cnf = TS_CONFIG_HTTP_BACKGROUND_FILL_ACTIVE_TIMEOUT ;
 }
 break ;
 }
 break ;
 }
 break ;
 case 49 : if ( ! strncmp ( name , "proxy.config.http.attach_server_session_to_client" , length ) ) {
 cnf = TS_CONFIG_HTTP_ATTACH_SERVER_SESSION_TO_CLIENT ;
 }
 break ;
 case 50 : if ( ! strncmp ( name , "proxy.config.http.cache.cache_responses_to_cookies" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_CACHE_RESPONSES_TO_COOKIES ;
 }
 break ;
 case 51 : switch ( name [ length - 1 ] ) {
 case 'n' : if ( ! strncmp ( name , "proxy.config.http.keep_alive_no_activity_timeout_in" , length ) ) {
 cnf = TS_CONFIG_HTTP_KEEP_ALIVE_NO_ACTIVITY_TIMEOUT_IN ;
 }
 break ;
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.post.check.content_length.enabled" , length ) ) {
 cnf = TS_CONFIG_HTTP_POST_CHECK_CONTENT_LENGTH_ENABLED ;
 }
 break ;
 }
 break ;
 case 52 : switch ( name [ length - 1 ] ) {
 case 'c' : if ( ! strncmp ( name , "proxy.config.http.cache.cache_urls_that_look_dynamic" , length ) ) {
 cnf = TS_CONFIG_HTTP_CACHE_CACHE_URLS_THAT_LOOK_DYNAMIC ;
 }
 break ;
 case 'n' : if ( ! strncmp ( name , "proxy.config.http.transaction_no_activity_timeout_in" , length ) ) {
 cnf = TS_CONFIG_HTTP_TRANSACTION_NO_ACTIVITY_TIMEOUT_IN ;
 }
 break ;
 case 't' : if ( ! strncmp ( name , "proxy.config.http.keep_alive_no_activity_timeout_out" , length ) ) {
 cnf = TS_CONFIG_HTTP_KEEP_ALIVE_NO_ACTIVITY_TIMEOUT_OUT ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.uncacheable_requests_bypass_parent" , length ) ) {
 cnf = TS_CONFIG_HTTP_UNCACHEABLE_REQUESTS_BYPASS_PARENT ;
 }
 break ;
 }
 break ;
 case 53 : switch ( name [ length - 1 ] ) {
 case 't' : if ( ! strncmp ( name , "proxy.config.http.transaction_no_activity_timeout_out" , length ) ) {
 cnf = TS_CONFIG_HTTP_TRANSACTION_NO_ACTIVITY_TIMEOUT_OUT ;
 }
 break ;
 case 'd' : if ( ! strncmp ( name , "proxy.config.http.background_fill_completed_threshold" , length ) ) {
 typ = TS_RECORDDATATYPE_FLOAT ;
 cnf = TS_CONFIG_HTTP_BACKGROUND_FILL_COMPLETED_THRESHOLD ;
 }
 break ;
 case 's' : if ( ! strncmp ( name , "proxy.config.http.parent_proxy.total_connect_attempts" , length ) ) {
 cnf = TS_CONFIG_HTTP_PARENT_PROXY_TOTAL_CONNECT_ATTEMPTS ;
 }
 break ;
 }
 break ;
 case 55 : if ( ! strncmp ( name , "proxy.config.http.parent_proxy.connect_attempts_timeout" , length ) ) {
 cnf = TS_CONFIG_HTTP_PARENT_CONNECT_ATTEMPT_TIMEOUT ;
 }
 break ;
 case 58 : if ( ! strncmp ( name , "proxy.config.http.connect_attempts_max_retries_dead_server" , length ) ) {
 cnf = TS_CONFIG_HTTP_CONNECT_ATTEMPTS_MAX_RETRIES_DEAD_SERVER ;
 }
 else if ( ! strncmp ( name , "proxy.config.http.parent_proxy.per_parent_connect_attempts" , length ) ) {
 cnf = TS_CONFIG_HTTP_PER_PARENT_CONNECT_ATTEMPTS ;
 }
 break ;
 }
 * conf = cnf ;
 if ( type ) {
 * type = typ ;
 }
 return ( ( cnf != TS_CONFIG_NULL ) ? TS_SUCCESS : TS_ERROR ) ;
 }