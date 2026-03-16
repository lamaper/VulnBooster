TSReturnCode TSHttpArgIndexLookup ( int arg_idx , const char * * name , const char * * description ) {
 if ( sdk_sanity_check_null_ptr ( name ) == TS_SUCCESS ) {
 if ( state_arg_table [ arg_idx ] . name ) {
 * name = state_arg_table [ arg_idx ] . name ;
 if ( description ) {
 * description = state_arg_table [ arg_idx ] . description ;
 }
 return TS_SUCCESS ;
 }
 }
 return TS_ERROR ;
 }