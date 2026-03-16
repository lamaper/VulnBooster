static Node * substitute_actual_parameters ( Node * expr , int nargs , List * args , int * usecounts ) {
 substitute_actual_parameters_context context ;
 context . nargs = nargs ;
 context . args = args ;
 context . usecounts = usecounts ;
 return substitute_actual_parameters_mutator ( expr , & context ) ;
 }