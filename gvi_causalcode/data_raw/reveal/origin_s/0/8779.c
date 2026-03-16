bool contain_agg_clause ( Node * clause ) {
 return contain_agg_clause_walker ( clause , NULL ) ;
 }