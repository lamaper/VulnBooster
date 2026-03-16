static Datum ExecEvalXml ( XmlExprState * xmlExpr , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 XmlExpr * xexpr = ( XmlExpr * ) xmlExpr -> xprstate . expr ;
 Datum value ;
 bool isnull ;
 ListCell * arg ;
 ListCell * narg ;
 if ( isDone ) * isDone = ExprSingleResult ;
 * isNull = true ;
 switch ( xexpr -> op ) {
 case IS_XMLCONCAT : {
 List * values = NIL ;
 foreach ( arg , xmlExpr -> args ) {
 ExprState * e = ( ExprState * ) lfirst ( arg ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( ! isnull ) values = lappend ( values , DatumGetPointer ( value ) ) ;
 }
 if ( list_length ( values ) > 0 ) {
 * isNull = false ;
 return PointerGetDatum ( xmlconcat ( values ) ) ;
 }
 else return ( Datum ) 0 ;
 }
 break ;
 case IS_XMLFOREST : {
 StringInfoData buf ;
 initStringInfo ( & buf ) ;
 forboth ( arg , xmlExpr -> named_args , narg , xexpr -> arg_names ) {
 ExprState * e = ( ExprState * ) lfirst ( arg ) ;
 char * argname = strVal ( lfirst ( narg ) ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( ! isnull ) {
 appendStringInfo ( & buf , "<%s>%s</%s>" , argname , map_sql_value_to_xml_value ( value , exprType ( ( Node * ) e -> expr ) , true ) , argname ) ;
 * isNull = false ;
 }
 }
 if ( * isNull ) {
 pfree ( buf . data ) ;
 return ( Datum ) 0 ;
 }
 else {
 text * result ;
 result = cstring_to_text_with_len ( buf . data , buf . len ) ;
 pfree ( buf . data ) ;
 return PointerGetDatum ( result ) ;
 }
 }
 break ;
 case IS_XMLELEMENT : * isNull = false ;
 return PointerGetDatum ( xmlelement ( xmlExpr , econtext ) ) ;
 break ;
 case IS_XMLPARSE : {
 ExprState * e ;
 text * data ;
 bool preserve_whitespace ;
 Assert ( list_length ( xmlExpr -> args ) == 2 ) ;
 e = ( ExprState * ) linitial ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) return ( Datum ) 0 ;
 data = DatumGetTextP ( value ) ;
 e = ( ExprState * ) lsecond ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) return ( Datum ) 0 ;
 preserve_whitespace = DatumGetBool ( value ) ;
 * isNull = false ;
 return PointerGetDatum ( xmlparse ( data , xexpr -> xmloption , preserve_whitespace ) ) ;
 }
 break ;
 case IS_XMLPI : {
 ExprState * e ;
 text * arg ;
 Assert ( list_length ( xmlExpr -> args ) <= 1 ) ;
 if ( xmlExpr -> args ) {
 e = ( ExprState * ) linitial ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) arg = NULL ;
 else arg = DatumGetTextP ( value ) ;
 }
 else {
 arg = NULL ;
 isnull = false ;
 }
 return PointerGetDatum ( xmlpi ( xexpr -> name , arg , isnull , isNull ) ) ;
 }
 break ;
 case IS_XMLROOT : {
 ExprState * e ;
 xmltype * data ;
 text * version ;
 int standalone ;
 Assert ( list_length ( xmlExpr -> args ) == 3 ) ;
 e = ( ExprState * ) linitial ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) return ( Datum ) 0 ;
 data = DatumGetXmlP ( value ) ;
 e = ( ExprState * ) lsecond ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) version = NULL ;
 else version = DatumGetTextP ( value ) ;
 e = ( ExprState * ) lthird ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 standalone = DatumGetInt32 ( value ) ;
 * isNull = false ;
 return PointerGetDatum ( xmlroot ( data , version , standalone ) ) ;
 }
 break ;
 case IS_XMLSERIALIZE : {
 ExprState * e ;
 Assert ( list_length ( xmlExpr -> args ) == 1 ) ;
 e = ( ExprState * ) linitial ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) return ( Datum ) 0 ;
 * isNull = false ;
 return PointerGetDatum ( xmltotext_with_xmloption ( DatumGetXmlP ( value ) , xexpr -> xmloption ) ) ;
 }
 break ;
 case IS_DOCUMENT : {
 ExprState * e ;
 Assert ( list_length ( xmlExpr -> args ) == 1 ) ;
 e = ( ExprState * ) linitial ( xmlExpr -> args ) ;
 value = ExecEvalExpr ( e , econtext , & isnull , NULL ) ;
 if ( isnull ) return ( Datum ) 0 ;
 else {
 * isNull = false ;
 return BoolGetDatum ( xml_is_document ( DatumGetXmlP ( value ) ) ) ;
 }
 }
 break ;
 }
 elog ( ERROR , "unrecognized XML operation" ) ;
 return ( Datum ) 0 ;
 }