bool matchesOrigin ( const url : : Origin & origin , const GURL & url ) {
 return origin . IsSameOriginWith ( url : : Origin ( url ) ) ;
 }