bool contain_nonstrict_functions ( Node * clause ) {
 return contain_nonstrict_functions_walker ( clause , NULL ) ;
 }