inline static bool does_method_require_cache_copy_deletion ( const HttpConfigParams * http_config_param , const int method ) {
 return ( ( method != HTTP_WKSIDX_GET ) && ( method == HTTP_WKSIDX_DELETE || method == HTTP_WKSIDX_PURGE || method == HTTP_WKSIDX_PUT || ( http_config_param -> cache_post_method != 1 && method == HTTP_WKSIDX_POST ) ) ) ;
 }