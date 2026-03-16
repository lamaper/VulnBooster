bool contain_volatile_functions ( Node * clause ) {
 return contain_volatile_functions_walker ( clause , NULL ) ;
 }