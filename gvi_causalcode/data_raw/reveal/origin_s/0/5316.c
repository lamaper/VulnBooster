List * find_nonnullable_vars ( Node * clause ) {
 return find_nonnullable_vars_walker ( clause , true ) ;
 }