bool processSQLNamePattern ( PGconn * conn , PQExpBuffer buf , const char * pattern , bool have_where , bool force_escape , const char * schemavar , const char * namevar , const char * altnamevar , const char * visibilityrule ) {
 PQExpBufferData schemabuf ;
 PQExpBufferData namebuf ;
 int encoding = PQclientEncoding ( conn ) ;
 bool inquotes ;
 const char * cp ;
 int i ;
 bool added_clause = false ;

 if ( visibilityrule ) {
 WHEREAND ( ) ;
 appendPQExpBuffer ( buf , "%s\n" , visibilityrule ) ;
 }
 return added_clause ;
 }
 initPQExpBuffer ( & schemabuf ) ;
 initPQExpBuffer ( & namebuf ) ;
 appendPQExpBufferStr ( & namebuf , "^(" ) ;
 inquotes = false ;
 cp = pattern ;
 while ( * cp ) {
 char ch = * cp ;
 if ( ch == '"' ) {
 if ( inquotes && cp [ 1 ] == '"' ) {
 appendPQExpBufferChar ( & namebuf , '"' ) ;
 cp ++ ;
 }
 else inquotes = ! inquotes ;
 cp ++ ;
 }
 else if ( ! inquotes && isupper ( ( unsigned char ) ch ) ) {
 appendPQExpBufferChar ( & namebuf , pg_tolower ( ( unsigned char ) ch ) ) ;
 cp ++ ;
 }
 else if ( ! inquotes && ch == '*' ) {
 appendPQExpBufferStr ( & namebuf , ".*" ) ;
 cp ++ ;
 }
 else if ( ! inquotes && ch == '?' ) {
 appendPQExpBufferChar ( & namebuf , '.' ) ;
 cp ++ ;
 }
 else if ( ! inquotes && ch == '.' ) {
 resetPQExpBuffer ( & schemabuf ) ;
 appendPQExpBufferStr ( & schemabuf , namebuf . data ) ;
 resetPQExpBuffer ( & namebuf ) ;
 appendPQExpBufferStr ( & namebuf , "^(" ) ;
 cp ++ ;
 }
 else if ( ch == '$' ) {
 appendPQExpBufferStr ( & namebuf , "\\$" ) ;
 cp ++ ;
 }
 else {
 if ( ( inquotes || force_escape ) && strchr ( "|*+?()[]{
}
.^$\\" , ch ) ) appendPQExpBufferChar ( & namebuf , '\\' ) ;
 i = PQmblen ( cp , encoding ) ;
 while ( i -- && * cp ) {
 appendPQExpBufferChar ( & namebuf , * cp ) ;
 cp ++ ;
 }
 }
 }
 if ( namebuf . len > 2 ) {
 appendPQExpBufferStr ( & namebuf , ")$" ) ;
 if ( strcmp ( namebuf . data , "^(.*)$" ) != 0 ) {
 WHEREAND ( ) ;
 if ( altnamevar ) {
 appendPQExpBuffer ( buf , "(%s ~ " , namevar ) ;
 appendStringLiteralConn ( buf , namebuf . data , conn ) ;
 appendPQExpBuffer ( buf , "\n OR %s ~ " , altnamevar ) ;
 appendStringLiteralConn ( buf , namebuf . data , conn ) ;
 appendPQExpBufferStr ( buf , ")\n" ) ;
 }
 else {
 appendPQExpBuffer ( buf , "%s ~ " , namevar ) ;
 appendStringLiteralConn ( buf , namebuf . data , conn ) ;
 appendPQExpBufferChar ( buf , '\n' ) ;
 }
 }
 }
 if ( schemabuf . len > 2 ) {
 appendPQExpBufferStr ( & schemabuf , ")$" ) ;
 if ( strcmp ( schemabuf . data , "^(.*)$" ) != 0 && schemavar ) {
 WHEREAND ( ) ;
 appendPQExpBuffer ( buf , "%s ~ " , schemavar ) ;
 appendStringLiteralConn ( buf , schemabuf . data , conn ) ;
 appendPQExpBufferChar ( buf , '\n' ) ;
 }
 }
 else {
 if ( visibilityrule ) {
 WHEREAND ( ) ;
 appendPQExpBuffer ( buf , "%s\n" , visibilityrule ) ;
 }
 }
 termPQExpBuffer ( & schemabuf ) ;
 termPQExpBuffer ( & namebuf ) ;
 return added_clause ;
