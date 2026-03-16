const char * fmtQualifiedId ( int remoteVersion , const char * schema , const char * id ) {
 PQExpBuffer id_return ;
 PQExpBuffer lcl_pqexp = createPQExpBuffer ( ) ;
 if ( remoteVersion >= 70300 && schema && * schema ) {
 appendPQExpBuffer ( lcl_pqexp , "%s." , fmtId ( schema ) ) ;
 }
 appendPQExpBufferStr ( lcl_pqexp , fmtId ( id ) ) ;
 id_return = getLocalPQExpBuffer ( ) ;
 appendPQExpBufferStr ( id_return , lcl_pqexp -> data ) ;
 destroyPQExpBuffer ( lcl_pqexp ) ;
 return id_return -> data ;
 }