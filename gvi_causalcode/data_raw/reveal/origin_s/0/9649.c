static void add_user_option ( String * grant , ulong value , const char * name ) {
 if ( value ) {
 char buff [ 22 ] , * p ;
 grant -> append ( ' ' ) ;
 grant -> append ( name , strlen ( name ) ) ;
 grant -> append ( ' ' ) ;
 p = int10_to_str ( value , buff , 10 ) ;
 grant -> append ( buff , p - buff ) ;
 }
 }