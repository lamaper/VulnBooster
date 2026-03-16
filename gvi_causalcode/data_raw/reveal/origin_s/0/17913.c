List * deconstruct_indexquals ( IndexPath * path ) {
 List * result = NIL ;
 IndexOptInfo * index = path -> indexinfo ;
 ListCell * lcc , * lci ;
 forboth ( lcc , path -> indexquals , lci , path -> indexqualcols ) {
 RestrictInfo * rinfo = ( RestrictInfo * ) lfirst ( lcc ) ;
 int indexcol = lfirst_int ( lci ) ;
 Expr * clause ;
 Node * leftop , * rightop ;
 IndexQualInfo * qinfo ;
 Assert ( IsA ( rinfo , RestrictInfo ) ) ;
 clause = rinfo -> clause ;
 qinfo = ( IndexQualInfo * ) palloc ( sizeof ( IndexQualInfo ) ) ;
 qinfo -> rinfo = rinfo ;
 qinfo -> indexcol = indexcol ;
 if ( IsA ( clause , OpExpr ) ) {
 qinfo -> clause_op = ( ( OpExpr * ) clause ) -> opno ;
 leftop = get_leftop ( clause ) ;
 rightop = get_rightop ( clause ) ;
 if ( match_index_to_operand ( leftop , indexcol , index ) ) {
 qinfo -> varonleft = true ;
 qinfo -> other_operand = rightop ;
 }
 else {
 Assert ( match_index_to_operand ( rightop , indexcol , index ) ) ;
 qinfo -> varonleft = false ;
 qinfo -> other_operand = leftop ;
 }
 }
 else if ( IsA ( clause , RowCompareExpr ) ) {
 RowCompareExpr * rc = ( RowCompareExpr * ) clause ;
 qinfo -> clause_op = linitial_oid ( rc -> opnos ) ;
 if ( match_index_to_operand ( ( Node * ) linitial ( rc -> largs ) , indexcol , index ) ) {
 qinfo -> varonleft = true ;
 qinfo -> other_operand = ( Node * ) rc -> rargs ;
 }
 else {
 Assert ( match_index_to_operand ( ( Node * ) linitial ( rc -> rargs ) , indexcol , index ) ) ;
 qinfo -> varonleft = false ;
 qinfo -> other_operand = ( Node * ) rc -> largs ;
 }
 }
 else if ( IsA ( clause , ScalarArrayOpExpr ) ) {
 ScalarArrayOpExpr * saop = ( ScalarArrayOpExpr * ) clause ;
 qinfo -> clause_op = saop -> opno ;
 Assert ( match_index_to_operand ( ( Node * ) linitial ( saop -> args ) , indexcol , index ) ) ;
 qinfo -> varonleft = true ;
 qinfo -> other_operand = ( Node * ) lsecond ( saop -> args ) ;
 }
 else if ( IsA ( clause , NullTest ) ) {
 qinfo -> clause_op = InvalidOid ;
 Assert ( match_index_to_operand ( ( Node * ) ( ( NullTest * ) clause ) -> arg , indexcol , index ) ) ;
 qinfo -> varonleft = true ;
 qinfo -> other_operand = NULL ;
 }
 else {
 elog ( ERROR , "unsupported indexqual type: %d" , ( int ) nodeTag ( clause ) ) ;
 }
 result = lappend ( result , qinfo ) ;
 }
 return result ;
 }