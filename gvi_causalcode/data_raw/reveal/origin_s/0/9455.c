void appendStringLiteralConn ( PQExpBuffer buf , const char * str , PGconn * conn ) {
 size_t length = strlen ( str ) ;
 if ( strchr ( str , '\\' ) != NULL && PQserverVersion ( conn ) >= 80100 ) {
 if ( buf -> len > 0 && buf -> data [ buf -> len - 1 ] != ' ' ) appendPQExpBufferChar ( buf , ' ' ) ;
 appendPQExpBufferChar ( buf , ESCAPE_STRING_SYNTAX ) ;
 appendStringLiteral ( buf , str , PQclientEncoding ( conn ) , false ) ;
 return ;
 }
 if ( ! enlargePQExpBuffer ( buf , 2 * length + 2 ) ) return ;
 appendPQExpBufferChar ( buf , '\'' ) ;
 buf -> len += PQescapeStringConn ( conn , buf -> data + buf -> len , str , length , NULL ) ;
 appendPQExpBufferChar ( buf , '\'' ) ;
 }