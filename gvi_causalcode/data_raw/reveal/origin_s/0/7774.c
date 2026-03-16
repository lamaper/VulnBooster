inline static bool does_method_effect_cache ( int method ) {
 return ( ( method == HTTP_WKSIDX_GET || method == HTTP_WKSIDX_DELETE || method == HTTP_WKSIDX_PURGE || method == HTTP_WKSIDX_PUT || method == HTTP_WKSIDX_POST ) ) ;
 }