int virLogFindOutput ( virLogOutputPtr * outputs , size_t noutputs , virLogDestination dest , const void * opaque ) {
 size_t i ;
 const char * name = opaque ;
 for ( i = 0 ;
 i < noutputs ;
 i ++ ) {
 if ( dest == outputs [ i ] -> dest && ( STREQ_NULLABLE ( outputs [ i ] -> name , name ) ) ) return i ;
 }
 return - 1 ;
 }