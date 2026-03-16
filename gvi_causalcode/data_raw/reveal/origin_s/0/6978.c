static bool contain_volatile_functions_not_nextval_checker ( Oid func_id , void * context ) {
 return ( func_id != F_NEXTVAL_OID && func_volatile ( func_id ) == PROVOLATILE_VOLATILE ) ;
 }