static Cost other_operands_eval_cost ( PlannerInfo * root , List * qinfos ) {
 Cost qual_arg_cost = 0 ;
 ListCell * lc ;
 foreach ( lc , qinfos ) {
 IndexQualInfo * qinfo = ( IndexQualInfo * ) lfirst ( lc ) ;
 QualCost index_qual_cost ;
 cost_qual_eval_node ( & index_qual_cost , qinfo -> other_operand , root ) ;
 qual_arg_cost += index_qual_cost . startup + index_qual_cost . per_tuple ;
 }
 return qual_arg_cost ;
 }