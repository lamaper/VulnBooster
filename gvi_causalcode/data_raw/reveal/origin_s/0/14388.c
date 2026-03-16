ArchiveHandle * CloneArchive ( ArchiveHandle * AH ) {
 ArchiveHandle * clone ;
 clone = ( ArchiveHandle * ) pg_malloc ( sizeof ( ArchiveHandle ) ) ;
 memcpy ( clone , AH , sizeof ( ArchiveHandle ) ) ;
 memset ( & ( clone -> sqlparse ) , 0 , sizeof ( clone -> sqlparse ) ) ;
 clone -> connection = NULL ;
 clone -> connCancel = NULL ;
 clone -> currUser = NULL ;
 clone -> currSchema = NULL ;
 clone -> currTablespace = NULL ;
 clone -> currWithOids = - 1 ;
 if ( clone -> savedPassword ) clone -> savedPassword = pg_strdup ( clone -> savedPassword ) ;
 clone -> public . n_errors = 0 ;
 if ( AH -> mode == archModeRead ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 Assert ( AH -> connection == NULL ) ;
 ConnectDatabase ( ( Archive * ) clone , ropt -> dbname , ropt -> pghost , ropt -> pgport , ropt -> username , ropt -> promptPassword ) ;
 _doSetFixedOutputState ( clone ) ;
 }
 else {
 PQExpBufferData connstr ;
 char * pghost ;
 char * pgport ;
 char * username ;
 Assert ( AH -> connection != NULL ) ;
 initPQExpBuffer ( & connstr ) ;
 appendPQExpBuffer ( & connstr , "dbname=" ) ;
 appendConnStrVal ( & connstr , PQdb ( AH -> connection ) ) ;
 pghost = PQhost ( AH -> connection ) ;
 pgport = PQport ( AH -> connection ) ;
 username = PQuser ( AH -> connection ) ;
 ConnectDatabase ( ( Archive * ) clone , connstr . data , pghost , pgport , username , TRI_NO ) ;
 termPQExpBuffer ( & connstr ) ;
 }
 ( clone -> ClonePtr ) ( clone ) ;
 Assert ( clone -> connection != NULL ) ;
 return clone ;
 }