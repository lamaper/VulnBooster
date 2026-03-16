inline static bool is_request_conditional ( HTTPHdr * header ) {
 uint64_t mask = ( MIME_PRESENCE_IF_UNMODIFIED_SINCE | MIME_PRESENCE_IF_MODIFIED_SINCE | MIME_PRESENCE_IF_RANGE | MIME_PRESENCE_IF_MATCH | MIME_PRESENCE_IF_NONE_MATCH ) ;
 return ( header -> presence ( mask ) && ( header -> method_get_wksidx ( ) == HTTP_WKSIDX_GET || header -> method_get_wksidx ( ) == HTTP_WKSIDX_HEAD ) ) ;
 }