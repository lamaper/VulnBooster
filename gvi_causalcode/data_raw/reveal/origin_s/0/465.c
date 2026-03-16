bool contain_mutable_functions ( Node * clause ) {
 return contain_mutable_functions_walker ( clause , NULL ) ;
 }