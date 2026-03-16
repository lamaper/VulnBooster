const char * fmtId ( const char * rawid ) {
 PQExpBuffer id_return = getLocalPQExpBuffer ( ) ;
 const char * cp ;
 bool need_quotes = false ;
 if ( quote_all_identifiers ) need_quotes = true ;
 else if ( ! ( ( rawid [ 0 ] >= 'a' && rawid [ 0 ] <= 'z' ) || rawid [ 0 ] == '_' ) ) need_quotes = true ;
 else {
 for ( cp = rawid ;
 * cp ;
 cp ++ ) {
 if ( ! ( ( * cp >= 'a' && * cp <= 'z' ) || ( * cp >= '0' && * cp <= '9' ) || ( * cp == '_' ) ) ) {
 need_quotes = true ;
 break ;
 }
 }
 }
 if ( ! need_quotes ) {
 const ScanKeyword * keyword = ScanKeywordLookup ( rawid , ScanKeywords , NumScanKeywords ) ;
 if ( keyword != NULL && keyword -> category != UNRESERVED_KEYWORD ) need_quotes = true ;
 }
 if ( ! need_quotes ) {
 appendPQExpBufferStr ( id_return , rawid ) ;
 }
 else {
 appendPQExpBufferChar ( id_return , '"' ) ;
 for ( cp = rawid ;
 * cp ;
 cp ++ ) {
 if ( * cp == '"' ) appendPQExpBufferChar ( id_return , '"' ) ;
 appendPQExpBufferChar ( id_return , * cp ) ;
 }
 appendPQExpBufferChar ( id_return , '"' ) ;
 }
 return id_return -> data ;
 }