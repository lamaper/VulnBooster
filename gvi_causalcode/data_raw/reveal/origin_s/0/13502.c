static PQExpBuffer defaultGetLocalPQExpBuffer ( void ) {
 static PQExpBuffer id_return = NULL ;
 if ( id_return ) {
 resetPQExpBuffer ( id_return ) ;
 }
 else {
 id_return = createPQExpBuffer ( ) ;
 }
 return id_return ;
 }