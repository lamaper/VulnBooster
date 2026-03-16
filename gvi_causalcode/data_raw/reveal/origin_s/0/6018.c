static int zexecn ( i_ctx_t * i_ctx_p ) {
 os_ptr op = osp ;
 uint n , i ;
 es_ptr esp_orig ;
 check_int_leu ( * op , max_uint - 1 ) ;
 n = ( uint ) op -> value . intval ;
 check_op ( n + 1 ) ;
 check_estack ( n ) ;
 esp_orig = esp ;
 for ( i = 0 ;
 i < n ;
 ++ i ) {
 const ref * rp = ref_stack_index ( & o_stack , ( long ) ( i + 1 ) ) ;
 if ( ref_type_uses_access ( r_type ( rp ) ) ) {
 if ( ! r_has_attr ( rp , a_execute ) && r_has_attr ( rp , a_executable ) ) {
 esp = esp_orig ;
 return_error ( gs_error_invalidaccess ) ;
 }
 }
 if ( ! r_has_type_attrs ( rp , t_null , a_executable ) ) {
 ++ esp ;
 ref_assign ( esp , rp ) ;
 }
 }
 esfile_check_cache ( ) ;
 pop ( n + 1 ) ;
 return o_push_estack ;
 }