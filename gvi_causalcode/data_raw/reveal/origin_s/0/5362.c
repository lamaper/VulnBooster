static int runPgDump ( const char * dbname ) {
 PQExpBuffer connstrbuf = createPQExpBuffer ( ) ;
 PQExpBuffer cmd = createPQExpBuffer ( ) ;
 int ret ;
 appendPQExpBuffer ( cmd , "\"%s\" %s" , pg_dump_bin , pgdumpopts -> data ) ;
 if ( filename ) appendPQExpBufferStr ( cmd , " -Fa " ) ;
 else appendPQExpBufferStr ( cmd , " -Fp " ) ;
 appendPQExpBuffer ( connstrbuf , "%s dbname=" , connstr ) ;
 appendConnStrVal ( connstrbuf , dbname ) ;
 appendShellString ( cmd , connstrbuf -> data ) ;
 if ( verbose ) fprintf ( stderr , _ ( "%s: running \"%s\"\n" ) , progname , cmd -> data ) ;
 fflush ( stdout ) ;
 fflush ( stderr ) ;
 ret = system ( cmd -> data ) ;
 destroyPQExpBuffer ( cmd ) ;
 destroyPQExpBuffer ( connstrbuf ) ;
 return ret ;
 }