Selectivity scalararraysel ( PlannerInfo * root , ScalarArrayOpExpr * clause , bool is_join_clause , int varRelid , JoinType jointype , SpecialJoinInfo * sjinfo ) {
 Oid operator = clause -> opno ;
 bool useOr = clause -> useOr ;
 bool isEquality = false ;
 bool isInequality = false ;
 Node * leftop ;
 Node * rightop ;
 Oid nominal_element_type ;
 Oid nominal_element_collation ;
 TypeCacheEntry * typentry ;
 RegProcedure oprsel ;
 FmgrInfo oprselproc ;
 Selectivity s1 ;
 Selectivity s1disjoint ;
 Assert ( list_length ( clause -> args ) == 2 ) ;
 leftop = ( Node * ) linitial ( clause -> args ) ;
 rightop = ( Node * ) lsecond ( clause -> args ) ;
 leftop = estimate_expression_value ( root , leftop ) ;
 rightop = estimate_expression_value ( root , rightop ) ;
 nominal_element_type = get_base_element_type ( exprType ( rightop ) ) ;
 if ( ! OidIsValid ( nominal_element_type ) ) return ( Selectivity ) 0.5 ;
 nominal_element_collation = exprCollation ( rightop ) ;
 rightop = strip_array_coercion ( rightop ) ;
 typentry = lookup_type_cache ( nominal_element_type , TYPECACHE_EQ_OPR ) ;
 if ( OidIsValid ( typentry -> eq_opr ) ) {
 if ( operator == typentry -> eq_opr ) isEquality = true ;
 else if ( get_negator ( operator ) == typentry -> eq_opr ) isInequality = true ;
 }
 if ( ( isEquality || isInequality ) && ! is_join_clause ) {
 s1 = scalararraysel_containment ( root , leftop , rightop , nominal_element_type , isEquality , useOr , varRelid ) ;
 if ( s1 >= 0.0 ) return s1 ;
 }
 if ( is_join_clause ) oprsel = get_oprjoin ( operator ) ;
 else oprsel = get_oprrest ( operator ) ;
 if ( ! oprsel ) return ( Selectivity ) 0.5 ;
 fmgr_info ( oprsel , & oprselproc ) ;
 if ( oprsel == F_EQSEL || oprsel == F_EQJOINSEL ) isEquality = true ;
 else if ( oprsel == F_NEQSEL || oprsel == F_NEQJOINSEL ) isInequality = true ;
 if ( rightop && IsA ( rightop , Const ) ) {
 Datum arraydatum = ( ( Const * ) rightop ) -> constvalue ;
 bool arrayisnull = ( ( Const * ) rightop ) -> constisnull ;
 ArrayType * arrayval ;
 int16 elmlen ;
 bool elmbyval ;
 char elmalign ;
 int num_elems ;
 Datum * elem_values ;
 bool * elem_nulls ;
 int i ;
 if ( arrayisnull ) return ( Selectivity ) 0.0 ;
 arrayval = DatumGetArrayTypeP ( arraydatum ) ;
 get_typlenbyvalalign ( ARR_ELEMTYPE ( arrayval ) , & elmlen , & elmbyval , & elmalign ) ;
 deconstruct_array ( arrayval , ARR_ELEMTYPE ( arrayval ) , elmlen , elmbyval , elmalign , & elem_values , & elem_nulls , & num_elems ) ;
 s1 = s1disjoint = ( useOr ? 0.0 : 1.0 ) ;
 for ( i = 0 ;
 i < num_elems ;
 i ++ ) {
 List * args ;
 Selectivity s2 ;
 args = list_make2 ( leftop , makeConst ( nominal_element_type , - 1 , nominal_element_collation , elmlen , elem_values [ i ] , elem_nulls [ i ] , elmbyval ) ) ;
 if ( is_join_clause ) s2 = DatumGetFloat8 ( FunctionCall5Coll ( & oprselproc , clause -> inputcollid , PointerGetDatum ( root ) , ObjectIdGetDatum ( operator ) , PointerGetDatum ( args ) , Int16GetDatum ( jointype ) , PointerGetDatum ( sjinfo ) ) ) ;
 else s2 = DatumGetFloat8 ( FunctionCall4Coll ( & oprselproc , clause -> inputcollid , PointerGetDatum ( root ) , ObjectIdGetDatum ( operator ) , PointerGetDatum ( args ) , Int32GetDatum ( varRelid ) ) ) ;
 if ( useOr ) {
 s1 = s1 + s2 - s1 * s2 ;
 if ( isEquality ) s1disjoint += s2 ;
 }
 else {
 s1 = s1 * s2 ;
 if ( isInequality ) s1disjoint += s2 - 1.0 ;
 }
 }
 if ( ( useOr ? isEquality : isInequality ) && s1disjoint >= 0.0 && s1disjoint <= 1.0 ) s1 = s1disjoint ;
 }
 else if ( rightop && IsA ( rightop , ArrayExpr ) && ! ( ( ArrayExpr * ) rightop ) -> multidims ) {
 ArrayExpr * arrayexpr = ( ArrayExpr * ) rightop ;
 int16 elmlen ;
 bool elmbyval ;
 ListCell * l ;
 get_typlenbyval ( arrayexpr -> element_typeid , & elmlen , & elmbyval ) ;
 s1 = s1disjoint = ( useOr ? 0.0 : 1.0 ) ;
 foreach ( l , arrayexpr -> elements ) {
 Node * elem = ( Node * ) lfirst ( l ) ;
 List * args ;
 Selectivity s2 ;
 args = list_make2 ( leftop , elem ) ;
 if ( is_join_clause ) s2 = DatumGetFloat8 ( FunctionCall5Coll ( & oprselproc , clause -> inputcollid , PointerGetDatum ( root ) , ObjectIdGetDatum ( operator ) , PointerGetDatum ( args ) , Int16GetDatum ( jointype ) , PointerGetDatum ( sjinfo ) ) ) ;
 else s2 = DatumGetFloat8 ( FunctionCall4Coll ( & oprselproc , clause -> inputcollid , PointerGetDatum ( root ) , ObjectIdGetDatum ( operator ) , PointerGetDatum ( args ) , Int32GetDatum ( varRelid ) ) ) ;
 if ( useOr ) {
 s1 = s1 + s2 - s1 * s2 ;
 if ( isEquality ) s1disjoint += s2 ;
 }
 else {
 s1 = s1 * s2 ;
 if ( isInequality ) s1disjoint += s2 - 1.0 ;
 }
 }
 if ( ( useOr ? isEquality : isInequality ) && s1disjoint >= 0.0 && s1disjoint <= 1.0 ) s1 = s1disjoint ;
 }
 else {
 CaseTestExpr * dummyexpr ;
 List * args ;
 Selectivity s2 ;
 int i ;
 dummyexpr = makeNode ( CaseTestExpr ) ;
 dummyexpr -> typeId = nominal_element_type ;
 dummyexpr -> typeMod = - 1 ;
 dummyexpr -> collation = clause -> inputcollid ;
 args = list_make2 ( leftop , dummyexpr ) ;
 if ( is_join_clause ) s2 = DatumGetFloat8 ( FunctionCall5Coll ( & oprselproc , clause -> inputcollid , PointerGetDatum ( root ) , ObjectIdGetDatum ( operator ) , PointerGetDatum ( args ) , Int16GetDatum ( jointype ) , PointerGetDatum ( sjinfo ) ) ) ;
 else s2 = DatumGetFloat8 ( FunctionCall4Coll ( & oprselproc , clause -> inputcollid , PointerGetDatum ( root ) , ObjectIdGetDatum ( operator ) , PointerGetDatum ( args ) , Int32GetDatum ( varRelid ) ) ) ;
 s1 = useOr ? 0.0 : 1.0 ;
 for ( i = 0 ;
 i < 10 ;
 i ++ ) {
 if ( useOr ) s1 = s1 + s2 - s1 * s2 ;
 else s1 = s1 * s2 ;
 }
 }
 CLAMP_PROBABILITY ( s1 ) ;
 return s1 ;
 }