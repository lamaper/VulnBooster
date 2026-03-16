bool statistic_proc_security_check ( VariableStatData * vardata , Oid func_oid ) {
 if ( vardata -> acl_ok ) return true ;
 if ( ! OidIsValid ( func_oid ) ) return false ;
 if ( get_func_leakproof ( func_oid ) ) return true ;
 ereport ( DEBUG2 , ( errmsg_internal ( "not using statistics because function \"%s\" is not leak-proof" , get_func_name ( func_oid ) ) ) ) ;
 return false ;
 }