static void _getObjectDescription ( PQExpBuffer buf , TocEntry * te , ArchiveHandle * AH ) {
 const char * type = te -> desc ;
 if ( strcmp ( type , "VIEW" ) == 0 || strcmp ( type , "SEQUENCE" ) == 0 || strcmp ( type , "MATERIALIZED VIEW" ) == 0 ) type = "TABLE" ;
 if ( strcmp ( type , "COLLATION" ) == 0 || strcmp ( type , "CONVERSION" ) == 0 || strcmp ( type , "DOMAIN" ) == 0 || strcmp ( type , "TABLE" ) == 0 || strcmp ( type , "TYPE" ) == 0 || strcmp ( type , "FOREIGN TABLE" ) == 0 || strcmp ( type , "TEXT SEARCH DICTIONARY" ) == 0 || strcmp ( type , "TEXT SEARCH CONFIGURATION" ) == 0 || strcmp ( type , "DATABASE" ) == 0 || strcmp ( type , "PROCEDURAL LANGUAGE" ) == 0 || strcmp ( type , "SCHEMA" ) == 0 || strcmp ( type , "FOREIGN DATA WRAPPER" ) == 0 || strcmp ( type , "SERVER" ) == 0 || strcmp ( type , "USER MAPPING" ) == 0 ) {
 appendPQExpBuffer ( buf , "%s %s" , type , fmtId ( te -> tag ) ) ;
 return ;
 }
 if ( strcmp ( type , "BLOB" ) == 0 ) {
 appendPQExpBuffer ( buf , "LARGE OBJECT %s" , te -> tag ) ;
 return ;
 }
 if ( strcmp ( type , "AGGREGATE" ) == 0 || strcmp ( type , "FUNCTION" ) == 0 || strcmp ( type , "OPERATOR" ) == 0 || strcmp ( type , "OPERATOR CLASS" ) == 0 || strcmp ( type , "OPERATOR FAMILY" ) == 0 ) {
 char * first = pg_strdup ( te -> dropStmt + 5 ) ;
 char * last ;
 last = first + strlen ( first ) - 1 ;
 while ( last >= first && ( * last == '\n' || * last == ';
' ) ) last -- ;
 * ( last + 1 ) = '\0' ;
 appendPQExpBufferStr ( buf , first ) ;
 free ( first ) ;
 return ;
 }
 write_msg ( modulename , "WARNING: don't know how to set owner for object type %s\n" , type ) ;
 }