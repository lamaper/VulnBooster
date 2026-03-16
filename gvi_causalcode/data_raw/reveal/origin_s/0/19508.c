static bool contain_mutable_functions_checker ( Oid func_id , void * context ) {
 return ( func_volatile ( func_id ) != PROVOLATILE_IMMUTABLE ) ;
 }