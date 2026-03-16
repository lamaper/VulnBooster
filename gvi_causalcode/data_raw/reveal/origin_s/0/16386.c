static void makeAlterConfigCommand ( PGconn * conn , const char * arrayitem , const char * type , const char * name , const char * type2 , const char * name2 ) {
 char * pos ;
 char * mine ;
 PQExpBuffer buf ;
 mine = pg_strdup ( arrayitem ) ;
 pos = strchr ( mine , '=' ) ;
 if ( pos == NULL ) {
 free ( mine ) ;
 return ;
 }
 buf = createPQExpBuffer ( ) ;
 * pos = 0 ;
 appendPQExpBuffer ( buf , "ALTER %s %s " , type , fmtId ( name ) ) ;
 if ( type2 != NULL && name2 != NULL ) appendPQExpBuffer ( buf , "IN %s %s " , type2 , fmtId ( name2 ) ) ;
 appendPQExpBuffer ( buf , "SET %s TO " , fmtId ( mine ) ) ;
 if ( pg_strcasecmp ( mine , "DateStyle" ) == 0 || pg_strcasecmp ( mine , "search_path" ) == 0 ) appendPQExpBufferStr ( buf , pos + 1 ) ;
 else appendStringLiteralConn ( buf , pos + 1 , conn ) ;
 appendPQExpBufferStr ( buf , ";
\n" ) ;
 fprintf ( OPF , "%s" , buf -> data ) ;
 destroyPQExpBuffer ( buf ) ;
 free ( mine ) ;
 }