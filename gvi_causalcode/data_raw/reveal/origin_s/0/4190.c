static List * add_predicate_to_quals ( IndexOptInfo * index , List * indexQuals ) {
 List * predExtraQuals = NIL ;
 ListCell * lc ;
 if ( index -> indpred == NIL ) return indexQuals ;
 foreach ( lc , index -> indpred ) {
 Node * predQual = ( Node * ) lfirst ( lc ) ;
 List * oneQual = list_make1 ( predQual ) ;
 if ( ! predicate_implied_by ( oneQual , indexQuals ) ) predExtraQuals = list_concat ( predExtraQuals , oneQual ) ;
 }
 return list_concat ( predExtraQuals , indexQuals ) ;
 }