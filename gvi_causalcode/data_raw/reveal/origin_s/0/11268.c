bool contain_leaked_vars ( Node * clause ) {
 return contain_leaked_vars_walker ( clause , NULL ) ;
 }