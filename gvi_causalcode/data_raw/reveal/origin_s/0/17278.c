static bool line_matches ( struct rule * rule , const char * command , const char * subcommand ) {
 bool okay = false ;
 if ( strcmp ( rule -> command , "ALL" ) == 0 ) okay = true ;
 if ( command != NULL && strcmp ( rule -> command , command ) == 0 ) okay = true ;
 if ( command == NULL && strcmp ( rule -> command , "EMPTY" ) == 0 ) okay = true ;
 if ( okay ) {
 if ( strcmp ( rule -> subcommand , "ALL" ) == 0 ) return true ;
 if ( subcommand != NULL && strcmp ( rule -> subcommand , subcommand ) == 0 ) return true ;
 if ( subcommand == NULL && strcmp ( rule -> subcommand , "EMPTY" ) == 0 ) return true ;
 }
 return false ;
 }