static bool is_strict_saop ( ScalarArrayOpExpr * expr , bool falseOK ) {
 Node * rightop ;
 set_sa_opfuncid ( expr ) ;
 if ( ! func_strict ( expr -> opfuncid ) ) return false ;
 if ( expr -> useOr && falseOK ) return true ;
 Assert ( list_length ( expr -> args ) == 2 ) ;
 rightop = ( Node * ) lsecond ( expr -> args ) ;
 if ( rightop && IsA ( rightop , Const ) ) {
 Datum arraydatum = ( ( Const * ) rightop ) -> constvalue ;
 bool arrayisnull = ( ( Const * ) rightop ) -> constisnull ;
 ArrayType * arrayval ;
 int nitems ;
 if ( arrayisnull ) return false ;
 arrayval = DatumGetArrayTypeP ( arraydatum ) ;
 nitems = ArrayGetNItems ( ARR_NDIM ( arrayval ) , ARR_DIMS ( arrayval ) ) ;
 if ( nitems > 0 ) return true ;
 }
 else if ( rightop && IsA ( rightop , ArrayExpr ) ) {
 ArrayExpr * arrayexpr = ( ArrayExpr * ) rightop ;
 if ( arrayexpr -> elements != NIL && ! arrayexpr -> multidims ) return true ;
 }
 return false ;
 }