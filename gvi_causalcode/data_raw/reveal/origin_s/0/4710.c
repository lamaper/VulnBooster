inline static bool do_cookies_prevent_caching ( int cookies_conf , HTTPHdr * request , HTTPHdr * response , HTTPHdr * cached_request = nullptr ) {
 enum CookiesConfig {
 COOKIES_CACHE_NONE = 0 , COOKIES_CACHE_ALL = 1 , COOKIES_CACHE_IMAGES = 2 , COOKIES_CACHE_ALL_BUT_TEXT = 3 , COOKIES_CACHE_ALL_BUT_TEXT_EXT = 4 }
 ;
 const char * content_type = nullptr ;
 int str_len ;

 ink_assert ( response -> type_get ( ) == HTTP_TYPE_RESPONSE ) ;
 if ( cached_request ) {
 ink_assert ( cached_request -> type_get ( ) == HTTP_TYPE_REQUEST ) ;
 }

 return false ;
 }
 if ( ! response -> presence ( MIME_PRESENCE_SET_COOKIE ) && ! request -> presence ( MIME_PRESENCE_COOKIE ) && ( cached_request == nullptr || ! cached_request -> presence ( MIME_PRESENCE_COOKIE ) ) ) {
 return false ;
 }
 if ( ( CookiesConfig ) cookies_conf == COOKIES_CACHE_NONE ) {
 return true ;
 }
 content_type = response -> value_get ( MIME_FIELD_CONTENT_TYPE , MIME_LEN_CONTENT_TYPE , & str_len ) ;
 if ( ( CookiesConfig ) cookies_conf == COOKIES_CACHE_IMAGES ) {
 if ( content_type && str_len >= 5 && memcmp ( content_type , "image" , 5 ) == 0 ) {
 return false ;
 }
 return true ;
 }
 if ( content_type && str_len >= 4 && memcmp ( content_type , "text" , 4 ) == 0 ) {
 if ( ( CookiesConfig ) cookies_conf == COOKIES_CACHE_ALL_BUT_TEXT_EXT && ( ( ! response -> presence ( MIME_PRESENCE_SET_COOKIE ) ) || response -> is_cache_control_set ( HTTP_VALUE_PUBLIC ) ) ) {
 return false ;
 }
 return true ;
 }
 return false ;
 }