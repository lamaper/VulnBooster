static void dumpTablespaces ( PGconn * conn ) {
 PGresult * res ;
 int i ;
 if ( server_version >= 90600 ) res = executeQuery ( conn , "SELECT oid, spcname, " "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, " "pg_catalog.pg_tablespace_location(oid), " "(SELECT pg_catalog.array_agg(acl) FROM (SELECT pg_catalog.unnest(coalesce(spcacl,pg_catalog.acldefault('t',spcowner))) AS acl " "EXCEPT SELECT pg_catalog.unnest(pg_catalog.acldefault('t',spcowner))) as foo)" "AS spcacl," "(SELECT pg_catalog.array_agg(acl) FROM (SELECT pg_catalog.unnest(pg_catalog.acldefault('t',spcowner)) AS acl " "EXCEPT SELECT pg_catalog.unnest(coalesce(spcacl,pg_catalog.acldefault('t',spcowner)))) as foo)" "AS rspcacl," "array_to_string(spcoptions, ', ')," "pg_catalog.shobj_description(oid, 'pg_tablespace') " "FROM pg_catalog.pg_tablespace " "WHERE spcname !~ '^pg_' " "ORDER BY 1" ) ;
 else if ( server_version >= 90200 ) res = executeQuery ( conn , "SELECT oid, spcname, " "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, " "pg_catalog.pg_tablespace_location(oid), spcacl, '' as rspcacl, " "array_to_string(spcoptions, ', ')," "pg_catalog.shobj_description(oid, 'pg_tablespace') " "FROM pg_catalog.pg_tablespace " "WHERE spcname !~ '^pg_' " "ORDER BY 1" ) ;
 else if ( server_version >= 90000 ) res = executeQuery ( conn , "SELECT oid, spcname, " "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, " "spclocation, spcacl, '' as rspcacl, " "array_to_string(spcoptions, ', ')," "pg_catalog.shobj_description(oid, 'pg_tablespace') " "FROM pg_catalog.pg_tablespace " "WHERE spcname !~ '^pg_' " "ORDER BY 1" ) ;
 else if ( server_version >= 80200 ) res = executeQuery ( conn , "SELECT oid, spcname, " "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, " "spclocation, spcacl, '' as rspcacl, null, " "pg_catalog.shobj_description(oid, 'pg_tablespace') " "FROM pg_catalog.pg_tablespace " "WHERE spcname !~ '^pg_' " "ORDER BY 1" ) ;
 else res = executeQuery ( conn , "SELECT oid, spcname, " "pg_catalog.pg_get_userbyid(spcowner) AS spcowner, " "spclocation, spcacl, '' as rspcacl, " "null, null " "FROM pg_catalog.pg_tablespace " "WHERE spcname !~ '^pg_' " "ORDER BY 1" ) ;
 if ( PQntuples ( res ) > 0 ) fprintf ( OPF , "--\n-- Tablespaces\n--\n\n" ) ;
 for ( i = 0 ;
 i < PQntuples ( res ) ;
 i ++ ) {
 PQExpBuffer buf = createPQExpBuffer ( ) ;
 uint32 spcoid = atooid ( PQgetvalue ( res , i , 0 ) ) ;
 char * spcname = PQgetvalue ( res , i , 1 ) ;
 char * spcowner = PQgetvalue ( res , i , 2 ) ;
 char * spclocation = PQgetvalue ( res , i , 3 ) ;
 char * spcacl = PQgetvalue ( res , i , 4 ) ;
 char * rspcacl = PQgetvalue ( res , i , 5 ) ;
 char * spcoptions = PQgetvalue ( res , i , 6 ) ;
 char * spccomment = PQgetvalue ( res , i , 7 ) ;
 char * fspcname ;
 fspcname = pg_strdup ( fmtId ( spcname ) ) ;
 appendPQExpBuffer ( buf , "CREATE TABLESPACE %s" , fspcname ) ;
 appendPQExpBuffer ( buf , " OWNER %s" , fmtId ( spcowner ) ) ;
 appendPQExpBufferStr ( buf , " LOCATION " ) ;
 appendStringLiteralConn ( buf , spclocation , conn ) ;
 appendPQExpBufferStr ( buf , ";
\n" ) ;
 if ( spcoptions && spcoptions [ 0 ] != '\0' ) appendPQExpBuffer ( buf , "ALTER TABLESPACE %s SET (%s);
\n" , fspcname , spcoptions ) ;
 if ( ! skip_acls && ! buildACLCommands ( fspcname , NULL , "TABLESPACE" , spcacl , rspcacl , spcowner , "" , server_version , buf ) ) {
 fprintf ( stderr , _ ( "%s: could not parse ACL list (%s) for tablespace \"%s\"\n" ) , progname , spcacl , fspcname ) ;
 PQfinish ( conn ) ;
 exit_nicely ( 1 ) ;
 }
 if ( spccomment && strlen ( spccomment ) ) {
 appendPQExpBuffer ( buf , "COMMENT ON TABLESPACE %s IS " , fspcname ) ;
 appendStringLiteralConn ( buf , spccomment , conn ) ;
 appendPQExpBufferStr ( buf , ";
\n" ) ;
 }
 if ( ! no_security_labels && server_version >= 90200 ) buildShSecLabels ( conn , "pg_tablespace" , spcoid , buf , "TABLESPACE" , fspcname ) ;
 fprintf ( OPF , "%s" , buf -> data ) ;
 free ( fspcname ) ;
 destroyPQExpBuffer ( buf ) ;
 }
 PQclear ( res ) ;
 fprintf ( OPF , "\n\n" ) ;
 }