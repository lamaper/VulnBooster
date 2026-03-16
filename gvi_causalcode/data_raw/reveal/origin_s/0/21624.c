static int sapi_uwsgi_send_headers ( sapi_headers_struct * sapi_headers TSRMLS_DC ) {
 sapi_header_struct * h ;
 zend_llist_position pos ;
 if ( SG ( request_info ) . no_headers == 1 ) {
 return SAPI_HEADER_SENT_SUCCESSFULLY ;
 }
 struct wsgi_request * wsgi_req = ( struct wsgi_request * ) SG ( server_context ) ;
 if ( ! SG ( sapi_headers ) . http_status_line ) {
 char status [ 4 ] ;
 int hrc = SG ( sapi_headers ) . http_response_code ;
 if ( ! hrc ) hrc = 200 ;
 uwsgi_num2str2n ( hrc , status , 4 ) ;
 if ( uwsgi_response_prepare_headers ( wsgi_req , status , 3 ) ) return SAPI_HEADER_SEND_FAILED ;
 }
 else {
 char * sl = SG ( sapi_headers ) . http_status_line ;
 if ( uwsgi_response_prepare_headers ( wsgi_req , sl + 9 , strlen ( sl + 9 ) ) ) return SAPI_HEADER_SEND_FAILED ;
 }
 h = zend_llist_get_first_ex ( & sapi_headers -> headers , & pos ) ;
 while ( h ) {
 uwsgi_response_add_header ( wsgi_req , NULL , 0 , h -> header , h -> header_len ) ;
 h = zend_llist_get_next_ex ( & sapi_headers -> headers , & pos ) ;
 }
 return SAPI_HEADER_SENT_SUCCESSFULLY ;
 }