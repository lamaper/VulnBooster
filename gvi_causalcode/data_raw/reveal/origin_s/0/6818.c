static bool has_parallel_hazard_checker ( Oid func_id , void * context ) {
 char proparallel = func_parallel ( func_id ) ;
 if ( ( ( has_parallel_hazard_arg * ) context ) -> allow_restricted ) return ( proparallel == PROPARALLEL_UNSAFE ) ;
 else return ( proparallel != PROPARALLEL_SAFE ) ;
 }