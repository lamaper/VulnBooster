static bool contain_context_dependent_node ( Node * clause ) {
 int flags = 0 ;
 return contain_context_dependent_node_walker ( clause , & flags ) ;
 }