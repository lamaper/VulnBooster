void url_rewrite_remap_request ( const UrlMappingContainer & mapping_container , URL * request_url , int method ) {
 URL * map_to = mapping_container . getToURL ( ) ;
 URL * map_from = mapping_container . getFromURL ( ) ;
 const char * toHost ;
 int toHostLen ;
 toHost = map_to -> host_get ( & toHostLen ) ;
 Debug ( "url_rewrite" , "%s: Remapping rule id: %d matched" , __func__ , mapping_container . getMapping ( ) -> map_id ) ;
 request_url -> host_set ( toHost , toHostLen ) ;
 request_url -> port_set ( map_to -> port_get_raw ( ) ) ;
 if ( HTTP_WKSIDX_CONNECT != method ) {
 const char * toScheme ;
 int toSchemeLen ;
 const char * requestPath ;
 int requestPathLen = 0 ;
 int fromPathLen = 0 ;
 const char * toPath ;
 int toPathLen ;
 toScheme = map_to -> scheme_get ( & toSchemeLen ) ;
 request_url -> scheme_set ( toScheme , toSchemeLen ) ;
 map_from -> path_get ( & fromPathLen ) ;
 toPath = map_to -> path_get ( & toPathLen ) ;
 requestPath = request_url -> path_get ( & requestPathLen ) ;
 char * newPath = static_cast < char * > ( alloca ( sizeof ( char ) * ( ( requestPathLen - fromPathLen ) + toPathLen + 8 ) ) ) ;
 int newPathLen = 0 ;
 * newPath = 0 ;
 if ( toPath ) {
 memcpy ( newPath , toPath , toPathLen ) ;
 newPathLen += toPathLen ;
 }
 if ( ! fromPathLen && requestPathLen && newPathLen && toPathLen && * ( newPath + newPathLen - 1 ) != '/' ) {
 * ( newPath + newPathLen ) = '/' ;
 newPathLen ++ ;
 }
 if ( requestPath ) {
 if ( requestPathLen < fromPathLen ) {
 if ( toPathLen && requestPath [ requestPathLen - 1 ] == '/' && toPath [ toPathLen - 1 ] == '/' ) {
 fromPathLen ++ ;
 }
 }
 else {
 if ( toPathLen && requestPath [ fromPathLen ] == '/' && toPath [ toPathLen - 1 ] == '/' ) {
 fromPathLen ++ ;
 }
 }
 if ( ( requestPathLen - fromPathLen ) > 0 ) {
 memcpy ( newPath + newPathLen , requestPath + fromPathLen , requestPathLen - fromPathLen ) ;
 newPathLen += ( requestPathLen - fromPathLen ) ;
 }
 }
 if ( * newPath == '/' ) {
 request_url -> path_set ( newPath + 1 , newPathLen - 1 ) ;
 }
 else {
 request_url -> path_set ( newPath , newPathLen ) ;
 }
 }
 }