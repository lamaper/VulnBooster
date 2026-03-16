const char * symbname ( u_short token ) {
 char * name ;
 if ( token < COUNTOF ( symb ) && symb [ token ] != NULL ) {
 name = symb [ token ] ;
 }
 else {
 LIB_GETBUF ( name ) ;
 snprintf ( name , LIB_BUFLENGTH , "%d" , token ) ;
 }
 return name ;
 }