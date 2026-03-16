static Query * substitute_actual_srf_parameters ( Query * expr , int nargs , List * args ) {
 substitute_actual_srf_parameters_context context ;
 context . nargs = nargs ;
 context . args = args ;
 context . sublevels_up = 1 ;
 return query_tree_mutator ( expr , substitute_actual_srf_parameters_mutator , & context , 0 ) ;
 }