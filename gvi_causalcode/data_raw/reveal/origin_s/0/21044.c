int uwsgi_php_request ( struct wsgi_request * wsgi_req ) {
 char real_filename [ PATH_MAX + 1 ] ;
 char * path_info = NULL ;
 size_t real_filename_len = 0 ;
 struct stat php_stat ;
 char * filename = NULL ;
 int force_empty_script_name = 0 ;
 zend_file_handle file_handle ;


 if ( uwsgi_parse_vars ( wsgi_req ) ) {
 return - 1 ;
 }
 char * orig_path_info = wsgi_req -> path_info ;
 uint16_t orig_path_info_len = wsgi_req -> path_info_len ;
 if ( uphp . docroot ) {
 wsgi_req -> document_root = uphp . docroot ;
 }
 else if ( ! wsgi_req -> document_root_len ) {
 wsgi_req -> document_root = uwsgi . cwd ;
 }
 else {
 char * sanitized_docroot = ecalloc ( 1 , PATH_MAX + 1 ) ;
 if ( ! uwsgi_expand_path ( wsgi_req -> document_root , wsgi_req -> document_root_len , sanitized_docroot ) ) {
 efree ( sanitized_docroot ) ;
 return - 1 ;
 }
 wsgi_req -> document_root = sanitized_docroot ;
 }
 wsgi_req -> document_root_len = strlen ( wsgi_req -> document_root ) ;
 if ( uphp . app ) {

 while ( bypass ) {
 if ( uwsgi_regexp_match ( bypass -> pattern , bypass -> pattern_extra , wsgi_req -> uri , wsgi_req -> uri_len ) >= 0 ) {
 goto oldstyle ;
 }
 bypass = bypass -> next ;
 }

 if ( wsgi_req -> path_info_len == 1 && wsgi_req -> path_info [ 0 ] == '/' ) {
 goto appready ;
 }
 if ( uphp . app_qs ) {
 size_t app_qs_len = strlen ( uphp . app_qs ) ;
 size_t qs_len = wsgi_req -> path_info_len + app_qs_len ;
 if ( wsgi_req -> query_string_len > 0 ) {
 qs_len += 1 + wsgi_req -> query_string_len ;
 }
 char * qs = ecalloc ( 1 , qs_len + 1 ) ;
 memcpy ( qs , uphp . app_qs , app_qs_len ) ;
 memcpy ( qs + app_qs_len , wsgi_req -> path_info , wsgi_req -> path_info_len ) ;
 if ( wsgi_req -> query_string_len > 0 ) {
 char * ptr = qs + app_qs_len + wsgi_req -> path_info_len ;
 * ptr = '&' ;
 memcpy ( ptr + 1 , wsgi_req -> query_string , wsgi_req -> query_string_len ) ;
 }
 wsgi_req -> query_string = qs ;
 wsgi_req -> query_string_len = qs_len ;
 }
 appready : wsgi_req -> path_info = "" ;
 wsgi_req -> path_info_len = 0 ;
 force_empty_script_name = 1 ;
 goto secure2 ;
 }

 if ( uwsgi_php_walk ( wsgi_req , filename , wsgi_req -> document_root , wsgi_req -> document_root_len , & path_info ) ) {
 free ( filename ) ;
 if ( uphp . fallback || uphp . fallback2 ) {
 if ( uphp . fallback ) {
 filename = uwsgi_str ( uphp . fallback ) ;
 }
 else {
 filename = uwsgi_concat2n ( wsgi_req -> document_root , strlen ( wsgi_req -> document_root ) , uphp . fallback2 , strlen ( uphp . fallback2 ) ) ;
 wsgi_req -> script_name = uphp . fallback2 ;
 wsgi_req -> script_name_len = strlen ( uphp . fallback2 ) ;
 }
 if ( uphp . fallback_qs ) {
 size_t fqs_len = strlen ( uphp . fallback_qs ) ;
 size_t new_qs_len = orig_path_info_len + fqs_len + 1 + wsgi_req -> query_string_len ;
 char * new_qs = ecalloc ( 1 , new_qs_len + 1 ) ;
 memcpy ( new_qs , uphp . fallback_qs , fqs_len ) ;
 new_qs [ fqs_len ] = '=' ;
 memcpy ( new_qs + fqs_len + 1 , orig_path_info , orig_path_info_len ) ;
 if ( wsgi_req -> query_string_len ) {
 new_qs [ fqs_len + 1 + orig_path_info_len ] = '&' ;
 memcpy ( new_qs + fqs_len + 2 + orig_path_info_len , wsgi_req -> query_string , wsgi_req -> query_string_len ) ;
 }
 wsgi_req -> query_string = new_qs ;
 wsgi_req -> query_string_len = new_qs_len ;
 }
 }
 else {
 uwsgi_404 ( wsgi_req ) ;
 return - 1 ;
 }
 }
 if ( path_info ) {
 wsgi_req -> path_info = path_info ;
 wsgi_req -> path_info_len = orig_path_info_len - ( path_info - orig_path_info ) ;
 }
 else {
 wsgi_req -> path_info = "" ;
 wsgi_req -> path_info_len = 0 ;
 }
 if ( ! realpath ( filename , real_filename ) ) {
 free ( filename ) ;
 uwsgi_404 ( wsgi_req ) ;
 return - 1 ;
 }
 free ( filename ) ;
 real_filename_len = strlen ( real_filename ) ;
 if ( uphp . allowed_docroot ) {
 struct uwsgi_string_list * usl = uphp . allowed_docroot ;
 while ( usl ) {
 if ( ! uwsgi_starts_with ( real_filename , real_filename_len , usl -> value , usl -> len ) ) {
 goto secure ;
 }
 usl = usl -> next ;
 }
 uwsgi_403 ( wsgi_req ) ;
 uwsgi_log ( "PHP security error: %s is not under an allowed docroot\n" , real_filename ) ;
 return - 1 ;
 }
 else if ( uphp . docroot ) {
 if ( ! uwsgi_starts_with ( real_filename , real_filename_len , uphp . docroot , uphp . docroot_len ) ) {
 goto secure ;
 }
 uwsgi_403 ( wsgi_req ) ;
 uwsgi_log ( "PHP security error: %s is not under the default docroot\n" , real_filename ) ;
 return - 1 ;
 }
 secure : if ( stat ( real_filename , & php_stat ) ) {
 uwsgi_404 ( wsgi_req ) ;
 return UWSGI_OK ;
 }
 if ( S_ISDIR ( php_stat . st_mode ) ) {
 if ( orig_path_info_len == 0 || ( orig_path_info_len > 0 && orig_path_info [ orig_path_info_len - 1 ] != '/' ) ) {
 wsgi_req -> path_info = orig_path_info ;
 wsgi_req -> path_info_len = orig_path_info_len ;
 uwsgi_redirect_to_slash ( wsgi_req ) ;
 return UWSGI_OK ;
 }
 struct uwsgi_string_list * upi = uphp . index ;
 real_filename [ real_filename_len ] = '/' ;
 real_filename_len ++ ;
 int found = 0 ;
 while ( upi ) {
 if ( real_filename_len + upi -> len + 1 < PATH_MAX ) {
 memcpy ( real_filename + real_filename_len , upi -> value , upi -> len + 1 ) ;
 if ( ! access ( real_filename , R_OK ) ) {
 found = 1 ;
 break ;
 }
 }
 upi = upi -> next ;
 }
 if ( ! found ) {
 uwsgi_404 ( wsgi_req ) ;
 return UWSGI_OK ;
 }
 real_filename_len = strlen ( real_filename ) ;
 }
 if ( uphp . allowed_ext ) {
 struct uwsgi_string_list * usl = uphp . allowed_ext ;
 while ( usl ) {
 if ( real_filename_len >= usl -> len ) {
 if ( ! uwsgi_strncmp ( real_filename + ( real_filename_len - usl -> len ) , usl -> len , usl -> value , usl -> len ) ) {
 goto secure2 ;
 }
 }
 usl = usl -> next ;
 }
 uwsgi_403 ( wsgi_req ) ;
 uwsgi_log ( "PHP security error: %s does not end with an allowed extension\n" , real_filename ) ;
 return - 1 ;
 }
 secure2 : wsgi_req -> file = real_filename ;
 wsgi_req -> file_len = strlen ( wsgi_req -> file ) ;
 if ( uphp . allowed_scripts ) {
 struct uwsgi_string_list * usl = uphp . allowed_scripts ;
 while ( usl ) {
 if ( ! uwsgi_strncmp ( wsgi_req -> file , wsgi_req -> file_len , usl -> value , usl -> len ) ) {
 goto secure3 ;
 }
 usl = usl -> next ;
 }
 uwsgi_403 ( wsgi_req ) ;
 uwsgi_log ( "PHP security error: %s is not an allowed script\n" , real_filename ) ;
 return - 1 ;
 }
 secure3 : if ( force_empty_script_name ) {
 wsgi_req -> script_name = "" ;
 wsgi_req -> script_name_len = 0 ;
 }
 else if ( ! uphp . fallback2 ) {
 wsgi_req -> script_name = orig_path_info ;
 if ( path_info ) {
 wsgi_req -> script_name_len = path_info - orig_path_info ;
 }
 else {
 wsgi_req -> script_name_len = orig_path_info_len ;
 }
 }


 SG ( request_info ) . request_method = estrndup ( wsgi_req -> method , wsgi_req -> method_len ) ;
 SG ( request_info ) . proto_num = 1001 ;
 SG ( request_info ) . query_string = estrndup ( wsgi_req -> query_string , wsgi_req -> query_string_len ) ;
 SG ( request_info ) . content_length = wsgi_req -> post_cl ;
 SG ( request_info ) . content_type = estrndup ( wsgi_req -> content_type , wsgi_req -> content_type_len ) ;
 SG ( sapi_headers ) . http_response_code = 200 ;
 SG ( request_info ) . path_translated = wsgi_req -> file ;
 file_handle . type = ZEND_HANDLE_FILENAME ;
 file_handle . filename = real_filename ;
 file_handle . free_filename = 0 ;
 file_handle . opened_path = NULL ;
 if ( php_request_startup ( TSRMLS_C ) == FAILURE ) {
 uwsgi_500 ( wsgi_req ) ;
 return - 1 ;
 }
 struct uwsgi_string_list * usl = NULL ;
 uwsgi_foreach ( usl , uphp . exec_before ) {
 if ( zend_eval_string_ex ( usl -> value , NULL , "uWSGI php exec before" , 1 TSRMLS_CC ) == FAILURE ) goto end ;
 }
 php_execute_script ( & file_handle TSRMLS_CC ) ;
 uwsgi_foreach ( usl , uphp . exec_after ) {
 if ( zend_eval_string_ex ( usl -> value , NULL , "uWSGI php exec after" , 1 TSRMLS_CC ) == FAILURE ) goto end ;
 }
 end : php_request_shutdown ( NULL ) ;
 return 0 ;
 }