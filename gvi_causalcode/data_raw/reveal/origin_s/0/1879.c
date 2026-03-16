static Datum ExecEvalCoerceViaIO ( CoerceViaIOState * iostate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 Datum result ;
 Datum inputval ;
 char * string ;
 inputval = ExecEvalExpr ( iostate -> arg , econtext , isNull , isDone ) ;
 if ( isDone && * isDone == ExprEndResult ) return inputval ;
 if ( * isNull ) string = NULL ;
 else string = OutputFunctionCall ( & iostate -> outfunc , inputval ) ;
 result = InputFunctionCall ( & iostate -> infunc , string , iostate -> intypioparam , - 1 ) ;
 return result ;
 }