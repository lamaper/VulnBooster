static bool gincost_scalararrayopexpr ( PlannerInfo * root , IndexOptInfo * index , IndexQualInfo * qinfo , double numIndexEntries , GinQualCounts * counts ) {
 int indexcol = qinfo -> indexcol ;
 Oid clause_op = qinfo -> clause_op ;
 Node * rightop = qinfo -> other_operand ;
 ArrayType * arrayval ;
 int16 elmlen ;
 bool elmbyval ;
 char elmalign ;
 int numElems ;
 Datum * elemValues ;
 bool * elemNulls ;
 GinQualCounts arraycounts ;
 int numPossible = 0 ;
 int i ;
 Assert ( ( ( ScalarArrayOpExpr * ) qinfo -> rinfo -> clause ) -> useOr ) ;
 rightop = estimate_expression_value ( root , rightop ) ;
 if ( IsA ( rightop , RelabelType ) ) rightop = ( Node * ) ( ( RelabelType * ) rightop ) -> arg ;
 if ( ! IsA ( rightop , Const ) ) {
 counts -> exactEntries ++ ;
 counts -> searchEntries ++ ;
 counts -> arrayScans *= estimate_array_length ( rightop ) ;
 return true ;
 }
 if ( ( ( Const * ) rightop ) -> constisnull ) return false ;
 arrayval = DatumGetArrayTypeP ( ( ( Const * ) rightop ) -> constvalue ) ;
 get_typlenbyvalalign ( ARR_ELEMTYPE ( arrayval ) , & elmlen , & elmbyval , & elmalign ) ;
 deconstruct_array ( arrayval , ARR_ELEMTYPE ( arrayval ) , elmlen , elmbyval , elmalign , & elemValues , & elemNulls , & numElems ) ;
 memset ( & arraycounts , 0 , sizeof ( arraycounts ) ) ;
 for ( i = 0 ;
 i < numElems ;
 i ++ ) {
 GinQualCounts elemcounts ;
 if ( elemNulls [ i ] ) continue ;
 memset ( & elemcounts , 0 , sizeof ( elemcounts ) ) ;
 if ( gincost_pattern ( index , indexcol , clause_op , elemValues [ i ] , & elemcounts ) ) {
 numPossible ++ ;
 if ( elemcounts . haveFullScan ) {
 elemcounts . partialEntries = 0 ;
 elemcounts . exactEntries = numIndexEntries ;
 elemcounts . searchEntries = numIndexEntries ;
 }
 arraycounts . partialEntries += elemcounts . partialEntries ;
 arraycounts . exactEntries += elemcounts . exactEntries ;
 arraycounts . searchEntries += elemcounts . searchEntries ;
 }
 }
 if ( numPossible == 0 ) {
 return false ;
 }
 counts -> partialEntries += arraycounts . partialEntries / numPossible ;
 counts -> exactEntries += arraycounts . exactEntries / numPossible ;
 counts -> searchEntries += arraycounts . searchEntries / numPossible ;
 counts -> arrayScans *= numPossible ;
 return true ;
 }