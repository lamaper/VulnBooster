void ConnectDatabase ( Archive * AHX , const char * dbname , const char * pghost , const char * pgport , const char * username , trivalue prompt_password ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 char * password ;
 bool new_pass ;
 if ( AH -> connection ) exit_horribly ( modulename , "already connected to a database\n" ) ;
 password = AH -> savedPassword ? pg_strdup ( AH -> savedPassword ) : NULL ;
 if ( prompt_password == TRI_YES && password == NULL ) {
 password = simple_prompt ( "Password: " , 100 , false ) ;
 if ( password == NULL ) exit_horribly ( modulename , "out of memory\n" ) ;
 }
 AH -> promptPassword = prompt_password ;
 do {
 const char * keywords [ 7 ] ;
 const char * values [ 7 ] ;
 keywords [ 0 ] = "host" ;
 values [ 0 ] = pghost ;
 keywords [ 1 ] = "port" ;
 values [ 1 ] = pgport ;
 keywords [ 2 ] = "user" ;
 values [ 2 ] = username ;
 keywords [ 3 ] = "password" ;
 values [ 3 ] = password ;
 keywords [ 4 ] = "dbname" ;
 values [ 4 ] = dbname ;
 keywords [ 5 ] = "fallback_application_name" ;
 values [ 5 ] = progname ;
 keywords [ 6 ] = NULL ;
 values [ 6 ] = NULL ;
 new_pass = false ;
 AH -> connection = PQconnectdbParams ( keywords , values , true ) ;
 if ( ! AH -> connection ) exit_horribly ( modulename , "failed to connect to database\n" ) ;
 if ( PQstatus ( AH -> connection ) == CONNECTION_BAD && PQconnectionNeedsPassword ( AH -> connection ) && password == NULL && prompt_password != TRI_NO ) {
 PQfinish ( AH -> connection ) ;
 password = simple_prompt ( "Password: " , 100 , false ) ;
 if ( password == NULL ) exit_horribly ( modulename , "out of memory\n" ) ;
 new_pass = true ;
 }
 }
 while ( new_pass ) ;
 if ( PQstatus ( AH -> connection ) == CONNECTION_BAD ) exit_horribly ( modulename , "connection to database \"%s\" failed: %s" , PQdb ( AH -> connection ) ? PQdb ( AH -> connection ) : "" , PQerrorMessage ( AH -> connection ) ) ;
 if ( PQconnectionUsedPassword ( AH -> connection ) ) {
 if ( AH -> savedPassword ) free ( AH -> savedPassword ) ;
 AH -> savedPassword = pg_strdup ( PQpass ( AH -> connection ) ) ;
 }
 if ( password ) free ( password ) ;
 _check_database_version ( AH ) ;
 PQsetNoticeProcessor ( AH -> connection , notice_processor , NULL ) ;
 set_archive_cancel_info ( AH , AH -> connection ) ;
 }