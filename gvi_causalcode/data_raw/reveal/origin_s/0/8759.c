int estimate_array_length ( Node * arrayexpr ) {
 arrayexpr = strip_array_coercion ( arrayexpr ) ;
 if ( arrayexpr && IsA ( arrayexpr , Const ) ) {
 Datum arraydatum = ( ( Const * ) arrayexpr ) -> constvalue ;
 bool arrayisnull = ( ( Const * ) arrayexpr ) -> constisnull ;
 ArrayType * arrayval ;
 if ( arrayisnull ) return 0 ;
 arrayval = DatumGetArrayTypeP ( arraydatum ) ;
 return ArrayGetNItems ( ARR_NDIM ( arrayval ) , ARR_DIMS ( arrayval ) ) ;
 }
 else if ( arrayexpr && IsA ( arrayexpr , ArrayExpr ) && ! ( ( ArrayExpr * ) arrayexpr ) -> multidims ) {
 return list_length ( ( ( ArrayExpr * ) arrayexpr ) -> elements ) ;
 }
 else {
 return 10 ;
 }
 }