Datum GetAttributeByName ( HeapTupleHeader tuple , const char * attname , bool * isNull ) {
 AttrNumber attrno ;
 Datum result ;
 Oid tupType ;
 int32 tupTypmod ;
 TupleDesc tupDesc ;
 HeapTupleData tmptup ;
 int i ;
 if ( attname == NULL ) elog ( ERROR , "invalid attribute name" ) ;
 if ( isNull == NULL ) elog ( ERROR , "a NULL isNull pointer was passed" ) ;
 if ( tuple == NULL ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 tupType = HeapTupleHeaderGetTypeId ( tuple ) ;
 tupTypmod = HeapTupleHeaderGetTypMod ( tuple ) ;
 tupDesc = lookup_rowtype_tupdesc ( tupType , tupTypmod ) ;
 attrno = InvalidAttrNumber ;
 for ( i = 0 ;
 i < tupDesc -> natts ;
 i ++ ) {
 if ( namestrcmp ( & ( tupDesc -> attrs [ i ] -> attname ) , attname ) == 0 ) {
 attrno = tupDesc -> attrs [ i ] -> attnum ;
 break ;
 }
 }
 if ( attrno == InvalidAttrNumber ) elog ( ERROR , "attribute \"%s\" does not exist" , attname ) ;
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( tuple ) ;
 ItemPointerSetInvalid ( & ( tmptup . t_self ) ) ;
 tmptup . t_tableOid = InvalidOid ;
 tmptup . t_data = tuple ;
 result = heap_getattr ( & tmptup , attrno , tupDesc , isNull ) ;
 ReleaseTupleDesc ( tupDesc ) ;
 return result ;
 }