static void append_user ( String * str , LEX_USER * user ) {
 if ( str -> length ( ) ) str -> append ( ',' ) ;
 str -> append ( '\'' ) ;
 str -> append ( user -> user . str ) ;
 str -> append ( STRING_WITH_LEN ( "'@'" ) ) ;
 str -> append ( user -> host . str ) ;
 str -> append ( '\'' ) ;
 }