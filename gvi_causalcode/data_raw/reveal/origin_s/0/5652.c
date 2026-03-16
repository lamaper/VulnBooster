static PGconn * get_db_conn ( ClusterInfo * cluster , const char * db_name ) {
 PQExpBufferData conn_opts ;
 PGconn * conn ;
 initPQExpBuffer ( & conn_opts ) ;
 appendPQExpBufferStr ( & conn_opts , "dbname=" ) ;
 appendConnStrVal ( & conn_opts , db_name ) ;
 appendPQExpBufferStr ( & conn_opts , " user=" ) ;
 appendConnStrVal ( & conn_opts , os_info . user ) ;
 appendPQExpBuffer ( & conn_opts , " port=%d" , cluster -> port ) ;
 if ( cluster -> sockdir ) {
 appendPQExpBufferStr ( & conn_opts , " host=" ) ;
 appendConnStrVal ( & conn_opts , cluster -> sockdir ) ;
 }
 conn = PQconnectdb ( conn_opts . data ) ;
 termPQExpBuffer ( & conn_opts ) ;
 return conn ;
 }