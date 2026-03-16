bool has_parallel_hazard ( Node * node , bool allow_restricted ) {
 has_parallel_hazard_arg context ;
 context . allow_restricted = allow_restricted ;
 return has_parallel_hazard_walker ( node , & context ) ;
 }