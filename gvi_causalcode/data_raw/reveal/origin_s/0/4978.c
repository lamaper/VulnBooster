bool contain_subplans ( Node * clause ) {
 return contain_subplans_walker ( clause , NULL ) ;
 }