TSReturnCode TSHttpArgIndexReserve ( const char * name , const char * description , int * arg_idx ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( arg_idx ) == TS_SUCCESS ) ;
 int ix = ink_atomic_increment ( & next_argv_index , 1 ) ;
 if ( ix < HTTP_SSN_TXN_MAX_USER_ARG ) {
 state_arg_table [ ix ] . name = ats_strdup ( name ) ;
 state_arg_table [ ix ] . name_len = strlen ( state_arg_table [ ix ] . name ) ;
 if ( description ) {
 state_arg_table [ ix ] . description = ats_strdup ( description ) ;
 }
 * arg_idx = ix ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }