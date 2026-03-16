static void _check_database_version ( ArchiveHandle * AH ) {
 const char * remoteversion_str ;
 int remoteversion ;
 PGresult * res ;
 remoteversion_str = PQparameterStatus ( AH -> connection , "server_version" ) ;
 remoteversion = PQserverVersion ( AH -> connection ) ;
 if ( remoteversion == 0 || ! remoteversion_str ) exit_horribly ( modulename , "could not get server_version from libpq\n" ) ;
 AH -> public . remoteVersionStr = pg_strdup ( remoteversion_str ) ;
 AH -> public . remoteVersion = remoteversion ;
 if ( ! AH -> archiveRemoteVersion ) AH -> archiveRemoteVersion = AH -> public . remoteVersionStr ;
 if ( remoteversion != PG_VERSION_NUM && ( remoteversion < AH -> public . minRemoteVersion || remoteversion > AH -> public . maxRemoteVersion ) ) {
 write_msg ( NULL , "server version: %s;
 %s version: %s\n" , remoteversion_str , progname , PG_VERSION ) ;
 exit_horribly ( NULL , "aborting because of server version mismatch\n" ) ;
 }
 if ( remoteversion >= 90000 ) {
 res = ExecuteSqlQueryForSingleRow ( ( Archive * ) AH , "SELECT pg_catalog.pg_is_in_recovery()" ) ;
 AH -> public . isStandby = ( strcmp ( PQgetvalue ( res , 0 , 0 ) , "t" ) == 0 ) ;
 PQclear ( res ) ;
 }
 else AH -> public . isStandby = false ;
 }