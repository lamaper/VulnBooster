bool contain_volatile_functions_not_nextval ( Node * clause ) {
 return contain_volatile_functions_not_nextval_walker ( clause , NULL ) ;
 }