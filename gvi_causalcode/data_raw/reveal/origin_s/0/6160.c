static bool contain_leaked_vars_checker ( Oid func_id , void * context ) {
 return ! get_func_leakproof ( func_id ) ;
 }