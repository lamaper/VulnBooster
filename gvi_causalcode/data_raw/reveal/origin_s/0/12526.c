static bool contain_nonstrict_functions_checker ( Oid func_id , void * context ) {
 return ! func_strict ( func_id ) ;
 }