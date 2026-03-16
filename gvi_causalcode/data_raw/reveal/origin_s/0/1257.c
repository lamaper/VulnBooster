int ReconnectToServer ( ArchiveHandle * AH , const char * dbname , const char * username ) {
 PGconn * newConn ;
 const char * newdbname ;
 const char * newusername ;
 if ( ! dbname ) newdbname = PQdb ( AH -> connection ) ;
 else newdbname = dbname ;
 if ( ! username ) newusername = PQuser ( AH -> connection ) ;
 else newusername = username ;
 if ( strcmp ( newdbname , PQdb ( AH -> connection ) ) == 0 && strcmp ( newusername , PQuser ( AH -> connection ) ) == 0 ) return 1 ;
 newConn = _connectDB ( AH , newdbname , newusername ) ;
 set_archive_cancel_info ( AH , newConn ) ;
 PQfinish ( AH -> connection ) ;
 AH -> connection = newConn ;
 return 1 ;
 }