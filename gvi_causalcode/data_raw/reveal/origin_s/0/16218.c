static bool gincost_opexpr ( PlannerInfo * root , IndexOptInfo * index , IndexQualInfo * qinfo , GinQualCounts * counts ) {
 int indexcol = qinfo -> indexcol ;
 Oid clause_op = qinfo -> clause_op ;
 Node * operand = qinfo -> other_operand ;
 if ( ! qinfo -> varonleft ) {
 clause_op = get_commutator ( clause_op ) ;
 }
 operand = estimate_expression_value ( root , operand ) ;
 if ( IsA ( operand , RelabelType ) ) operand = ( Node * ) ( ( RelabelType * ) operand ) -> arg ;
 if ( ! IsA ( operand , Const ) ) {
 counts -> exactEntries ++ ;
 counts -> searchEntries ++ ;
 return true ;
 }
 if ( ( ( Const * ) operand ) -> constisnull ) return false ;
 return gincost_pattern ( index , indexcol , clause_op , ( ( Const * ) operand ) -> constvalue , counts ) ;
 }