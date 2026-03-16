Node * estimate_expression_value ( PlannerInfo * root , Node * node ) {
 eval_const_expressions_context context ;
 context . boundParams = root -> glob -> boundParams ;
 context . root = NULL ;
 context . active_fns = NIL ;
 context . case_val = NULL ;
 context . estimate = true ;
 return eval_const_expressions_mutator ( node , & context ) ;
 }