static bool contain_volatile_functions_checker ( Oid func_id , void * context ) {
 return ( func_volatile ( func_id ) == PROVOLATILE_VOLATILE ) ;
 }