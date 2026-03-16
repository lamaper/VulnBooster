void appendStringLiteralDQ ( PQExpBuffer buf , const char * str , const char * dqprefix ) {
 static const char suffixes [ ] = "_XXXXXXX" ;
 int nextchar = 0 ;
 PQExpBuffer delimBuf = createPQExpBuffer ( ) ;
 appendPQExpBufferChar ( delimBuf , '$' ) ;
 if ( dqprefix ) appendPQExpBufferStr ( delimBuf , dqprefix ) ;
 while ( strstr ( str , delimBuf -> data ) != NULL ) {
 appendPQExpBufferChar ( delimBuf , suffixes [ nextchar ++ ] ) ;
 nextchar %= sizeof ( suffixes ) - 1 ;
 }
 appendPQExpBufferChar ( delimBuf , '$' ) ;
 appendPQExpBufferStr ( buf , delimBuf -> data ) ;
 appendPQExpBufferStr ( buf , str ) ;
 appendPQExpBufferStr ( buf , delimBuf -> data ) ;
 destroyPQExpBuffer ( delimBuf ) ;
 }