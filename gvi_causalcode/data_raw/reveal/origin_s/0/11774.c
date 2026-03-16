Oid get_equality_op_for_ordering_op ( Oid opno , bool * reverse ) {
 Oid result = InvalidOid ;
 Oid opfamily ;
 Oid opcintype ;
 int16 strategy ;
 if ( get_ordering_op_properties ( opno , & opfamily , & opcintype , & strategy ) ) {
 result = get_opfamily_member ( opfamily , opcintype , opcintype , BTEqualStrategyNumber ) ;
 if ( reverse ) * reverse = ( strategy == BTGreaterStrategyNumber ) ;
 }
 return result ;
 }