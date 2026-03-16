static void _printTocEntry ( ArchiveHandle * AH , TocEntry * te , bool isData , bool acl_pass ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 if ( acl_pass ) {
 if ( ! _tocEntryIsACL ( te ) ) return ;
 }
 else {
 if ( _tocEntryIsACL ( te ) ) return ;
 }
 if ( ! ( ropt -> dropSchema && ! ropt -> createDB ) ) {
 if ( strcmp ( te -> desc , "SCHEMA" ) == 0 && strcmp ( te -> tag , "public" ) == 0 ) return ;
 if ( strcmp ( te -> desc , "COMMENT" ) == 0 && strcmp ( te -> tag , "SCHEMA public" ) == 0 ) return ;
 }
 _becomeOwner ( AH , te ) ;
 _selectOutputSchema ( AH , te -> namespace ) ;
 _selectTablespace ( AH , te -> tablespace ) ;
 if ( strcmp ( te -> desc , "TABLE" ) == 0 ) _setWithOids ( AH , te ) ;
 if ( ! AH -> noTocComments ) {
 const char * pfx ;
 char * sanitized_name ;
 char * sanitized_schema ;
 char * sanitized_owner ;
 if ( isData ) pfx = "Data for " ;
 else pfx = "" ;
 ahprintf ( AH , "--\n" ) ;
 if ( AH -> public . verbose ) {
 ahprintf ( AH , "-- TOC entry %d (class %u OID %u)\n" , te -> dumpId , te -> catalogId . tableoid , te -> catalogId . oid ) ;
 if ( te -> nDeps > 0 ) {
 int i ;
 ahprintf ( AH , "-- Dependencies:" ) ;
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) ahprintf ( AH , " %d" , te -> dependencies [ i ] ) ;
 ahprintf ( AH , "\n" ) ;
 }
 }
 sanitized_name = replace_line_endings ( te -> tag ) ;
 if ( te -> namespace ) sanitized_schema = replace_line_endings ( te -> namespace ) ;
 else sanitized_schema = pg_strdup ( "-" ) ;
 if ( ! ropt -> noOwner ) sanitized_owner = replace_line_endings ( te -> owner ) ;
 else sanitized_owner = pg_strdup ( "-" ) ;
 ahprintf ( AH , "-- %sName: %s;
 Type: %s;
 Schema: %s;
 Owner: %s" , pfx , sanitized_name , te -> desc , sanitized_schema , sanitized_owner ) ;
 free ( sanitized_name ) ;
 free ( sanitized_schema ) ;
 free ( sanitized_owner ) ;
 if ( te -> tablespace && strlen ( te -> tablespace ) > 0 && ! ropt -> noTablespace ) {
 char * sanitized_tablespace ;
 sanitized_tablespace = replace_line_endings ( te -> tablespace ) ;
 ahprintf ( AH , ";
 Tablespace: %s" , sanitized_tablespace ) ;
 free ( sanitized_tablespace ) ;
 }
 ahprintf ( AH , "\n" ) ;
 if ( AH -> PrintExtraTocPtr != NULL ) ( * AH -> PrintExtraTocPtr ) ( AH , te ) ;
 ahprintf ( AH , "--\n\n" ) ;
 }
 if ( ropt -> noOwner && strcmp ( te -> desc , "SCHEMA" ) == 0 ) {
 ahprintf ( AH , "CREATE SCHEMA %s;
\n\n\n" , fmtId ( te -> tag ) ) ;
 }
 else {
 if ( strlen ( te -> defn ) > 0 ) ahprintf ( AH , "%s\n\n" , te -> defn ) ;
 }
 if ( ! ropt -> noOwner && ! ropt -> use_setsessauth && strlen ( te -> owner ) > 0 && strlen ( te -> dropStmt ) > 0 ) {
 if ( strcmp ( te -> desc , "AGGREGATE" ) == 0 || strcmp ( te -> desc , "BLOB" ) == 0 || strcmp ( te -> desc , "COLLATION" ) == 0 || strcmp ( te -> desc , "CONVERSION" ) == 0 || strcmp ( te -> desc , "DATABASE" ) == 0 || strcmp ( te -> desc , "DOMAIN" ) == 0 || strcmp ( te -> desc , "FUNCTION" ) == 0 || strcmp ( te -> desc , "OPERATOR" ) == 0 || strcmp ( te -> desc , "OPERATOR CLASS" ) == 0 || strcmp ( te -> desc , "OPERATOR FAMILY" ) == 0 || strcmp ( te -> desc , "PROCEDURAL LANGUAGE" ) == 0 || strcmp ( te -> desc , "SCHEMA" ) == 0 || strcmp ( te -> desc , "TABLE" ) == 0 || strcmp ( te -> desc , "TYPE" ) == 0 || strcmp ( te -> desc , "VIEW" ) == 0 || strcmp ( te -> desc , "MATERIALIZED VIEW" ) == 0 || strcmp ( te -> desc , "SEQUENCE" ) == 0 || strcmp ( te -> desc , "FOREIGN TABLE" ) == 0 || strcmp ( te -> desc , "TEXT SEARCH DICTIONARY" ) == 0 || strcmp ( te -> desc , "TEXT SEARCH CONFIGURATION" ) == 0 || strcmp ( te -> desc , "FOREIGN DATA WRAPPER" ) == 0 || strcmp ( te -> desc , "SERVER" ) == 0 ) {
 PQExpBuffer temp = createPQExpBuffer ( ) ;
 appendPQExpBufferStr ( temp , "ALTER " ) ;
 _getObjectDescription ( temp , te , AH ) ;
 appendPQExpBuffer ( temp , " OWNER TO %s;
" , fmtId ( te -> owner ) ) ;
 ahprintf ( AH , "%s\n\n" , temp -> data ) ;
 destroyPQExpBuffer ( temp ) ;
 }
 else if ( strcmp ( te -> desc , "CAST" ) == 0 || strcmp ( te -> desc , "CHECK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "CONSTRAINT" ) == 0 || strcmp ( te -> desc , "DEFAULT" ) == 0 || strcmp ( te -> desc , "FK CONSTRAINT" ) == 0 || strcmp ( te -> desc , "INDEX" ) == 0 || strcmp ( te -> desc , "RULE" ) == 0 || strcmp ( te -> desc , "TRIGGER" ) == 0 || strcmp ( te -> desc , "ROW SECURITY" ) == 0 || strcmp ( te -> desc , "POLICY" ) == 0 || strcmp ( te -> desc , "USER MAPPING" ) == 0 ) {
 }
 else {
 write_msg ( modulename , "WARNING: don't know how to set owner for object type %s\n" , te -> desc ) ;
 }
 }
 if ( acl_pass ) {
 if ( AH -> currUser ) free ( AH -> currUser ) ;
 AH -> currUser = NULL ;
 }
 }