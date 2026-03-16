static Cost orderby_operands_eval_cost ( PlannerInfo * root , IndexPath * path ) {
 Cost qual_arg_cost = 0 ;
 ListCell * lc ;
 foreach ( lc , path -> indexorderbys ) {
 Expr * clause = ( Expr * ) lfirst ( lc ) ;
 Node * other_operand ;
 QualCost index_qual_cost ;
 if ( IsA ( clause , OpExpr ) ) {
 other_operand = get_rightop ( clause ) ;
 }
 else {
 elog ( ERROR , "unsupported indexorderby type: %d" , ( int ) nodeTag ( clause ) ) ;
 other_operand = NULL ;
 }
 cost_qual_eval_node ( & index_qual_cost , other_operand , root ) ;
 qual_arg_cost += index_qual_cost . startup + index_qual_cost . per_tuple ;
 }
 return qual_arg_cost ;
 }