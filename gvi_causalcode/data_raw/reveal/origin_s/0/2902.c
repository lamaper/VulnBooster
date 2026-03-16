static void ExecuteSimpleCommands ( ArchiveHandle * AH , const char * buf , size_t bufLen ) {
 const char * qry = buf ;
 const char * eos = buf + bufLen ;
 if ( AH -> sqlparse . curCmd == NULL ) AH -> sqlparse . curCmd = createPQExpBuffer ( ) ;
 for ( ;
 qry < eos ;
 qry ++ ) {
 char ch = * qry ;
 if ( ! ( ch == '\n' && AH -> sqlparse . curCmd -> len == 0 ) ) appendPQExpBufferChar ( AH -> sqlparse . curCmd , ch ) ;
 switch ( AH -> sqlparse . state ) {
 case SQL_SCAN : if ( ch == ';
' ) {
 ExecuteSqlCommand ( AH , AH -> sqlparse . curCmd -> data , "could not execute query" ) ;
 resetPQExpBuffer ( AH -> sqlparse . curCmd ) ;
 }
 else if ( ch == '\'' ) {
 AH -> sqlparse . state = SQL_IN_SINGLE_QUOTE ;
 AH -> sqlparse . backSlash = false ;
 }
 else if ( ch == '"' ) {
 AH -> sqlparse . state = SQL_IN_DOUBLE_QUOTE ;
 }
 break ;
 case SQL_IN_SINGLE_QUOTE : if ( ch == '\'' && ! AH -> sqlparse . backSlash ) AH -> sqlparse . state = SQL_SCAN ;
 else if ( ch == '\\' && ! AH -> public . std_strings ) AH -> sqlparse . backSlash = ! AH -> sqlparse . backSlash ;
 else AH -> sqlparse . backSlash = false ;
 break ;
 case SQL_IN_DOUBLE_QUOTE : if ( ch == '"' ) AH -> sqlparse . state = SQL_SCAN ;
 break ;
 }
 }
 }