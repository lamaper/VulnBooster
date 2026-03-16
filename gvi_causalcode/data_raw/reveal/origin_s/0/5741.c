TSReturnCode TSHttpArgIndexNameLookup ( const char * name , int * arg_idx , const char * * description ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( arg_idx ) == TS_SUCCESS ) ;
 size_t len = strlen ( name ) ;
 for ( int ix = 0 ;
 ix < next_argv_index ;
 ++ ix ) {
 if ( ( len == state_arg_table [ ix ] . name_len ) && ( 0 == strcmp ( name , state_arg_table [ ix ] . name ) ) ) {
 if ( description ) {
 * description = state_arg_table [ ix ] . description ;
 }
 * arg_idx = ix ;
 return TS_SUCCESS ;
 }
 }
 return TS_ERROR ;
 }