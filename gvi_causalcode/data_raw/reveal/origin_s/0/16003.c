static void cpw_usage ( const char * str ) {
 if ( str ) fprintf ( stderr , "%s\n" , str ) ;
 fprintf ( stderr , _ ( "usage: change_password [-randkey] [-keepold] " "[-e keysaltlist] [-pw password] principal\n" ) ) ;
 }