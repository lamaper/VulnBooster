static void debugCB_print_log ( debugCBContext * q , const char * name ) {
 if ( q == NULL ) {
 printf ( "debugCBontext: %s is NULL!!\n" , name ) ;
 }
 else {
 if ( q -> magic != 0xC0FFEE ) {
 fprintf ( stderr , "debugCBContext: %p:%d's magic is %x, supposed to be 0xC0FFEE\n" , q , q -> serial , q -> magic ) ;
 }
 printf ( "debugCBContext %p:%d=%s - magic %x\n" , q , q -> serial , name , q -> magic ) ;
 }
 }