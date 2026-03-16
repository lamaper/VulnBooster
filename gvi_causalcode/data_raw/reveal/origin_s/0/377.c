Node * eval_const_expressions ( PlannerInfo * root , Node * node ) {
 eval_const_expressions_context context ;
 if ( root ) context . boundParams = root -> glob -> boundParams ;
 else context . boundParams = NULL ;
 context . root = root ;
 context . active_fns = NIL ;
 context . case_val = NULL ;
 context . estimate = false ;
 return eval_const_expressions_mutator ( node , & context ) ;
 }