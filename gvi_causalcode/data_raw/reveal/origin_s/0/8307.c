static Datum ExecEvalCoerceToDomain ( CoerceToDomainState * cstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 CoerceToDomain * ctest = ( CoerceToDomain * ) cstate -> xprstate . expr ;
 Datum result ;
 ListCell * l ;
 result = ExecEvalExpr ( cstate -> arg , econtext , isNull , isDone ) ;
 if ( isDone && * isDone == ExprEndResult ) return result ;
 UpdateDomainConstraintRef ( cstate -> constraint_ref ) ;
 foreach ( l , cstate -> constraint_ref -> constraints ) {
 DomainConstraintState * con = ( DomainConstraintState * ) lfirst ( l ) ;
 switch ( con -> constrainttype ) {
 case DOM_CONSTRAINT_NOTNULL : if ( * isNull ) ereport ( ERROR , ( errcode ( ERRCODE_NOT_NULL_VIOLATION ) , errmsg ( "domain %s does not allow null values" , format_type_be ( ctest -> resulttype ) ) , errdatatype ( ctest -> resulttype ) ) ) ;
 break ;
 case DOM_CONSTRAINT_CHECK : {
 Datum conResult ;
 bool conIsNull ;
 Datum save_datum ;
 bool save_isNull ;
 save_datum = econtext -> domainValue_datum ;
 save_isNull = econtext -> domainValue_isNull ;
 econtext -> domainValue_datum = result ;
 econtext -> domainValue_isNull = * isNull ;
 conResult = ExecEvalExpr ( con -> check_expr , econtext , & conIsNull , NULL ) ;
 if ( ! conIsNull && ! DatumGetBool ( conResult ) ) ereport ( ERROR , ( errcode ( ERRCODE_CHECK_VIOLATION ) , errmsg ( "value for domain %s violates check constraint \"%s\"" , format_type_be ( ctest -> resulttype ) , con -> name ) , errdomainconstraint ( ctest -> resulttype , con -> name ) ) ) ;
 econtext -> domainValue_datum = save_datum ;
 econtext -> domainValue_isNull = save_isNull ;
 break ;
 }
 default : elog ( ERROR , "unrecognized constraint type: %d" , ( int ) con -> constrainttype ) ;
 break ;
 }
 }
 return result ;
 }