char * cluster_conn_opts ( ClusterInfo * cluster ) {
 static PQExpBuffer buf ;
 if ( buf == NULL ) buf = createPQExpBuffer ( ) ;
 else resetPQExpBuffer ( buf ) ;
 if ( cluster -> sockdir ) {
 appendPQExpBufferStr ( buf , "--host " ) ;
 appendShellString ( buf , cluster -> sockdir ) ;
 appendPQExpBufferChar ( buf , ' ' ) ;
 }
 appendPQExpBuffer ( buf , "--port %d --username " , cluster -> port ) ;
 appendShellString ( buf , os_info . user ) ;
 return buf -> data ;
 }