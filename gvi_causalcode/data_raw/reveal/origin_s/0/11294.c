inline TSReturnCode ink_sanity_check_stat_structure ( void * obj ) {
 if ( obj == nullptr ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }