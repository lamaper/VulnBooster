static GURL ToAndFromOriginIdentifier ( const GURL origin_url ) {
 std : : string id = webkit_database : : GetIdentifierFromOrigin ( origin_url ) ;
 return webkit_database : : GetOriginFromIdentifier ( id ) ;
 }