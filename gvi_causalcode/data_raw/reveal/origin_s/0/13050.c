Datum GetAttributeByNum ( HeapTupleHeader tuple , AttrNumber attrno , bool * isNull ) {
 Datum result ;
 Oid tupType ;
 int32 tupTypmod ;
 TupleDesc tupDesc ;
 HeapTupleData tmptup ;
 if ( ! AttributeNumberIsValid ( attrno ) ) elog ( ERROR , "invalid attribute number %d" , attrno ) ;
 if ( isNull == NULL ) elog ( ERROR , "a NULL isNull pointer was passed" ) ;
 if ( tuple == NULL ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 tupType = HeapTupleHeaderGetTypeId ( tuple ) ;
 tupTypmod = HeapTupleHeaderGetTypMod ( tuple ) ;
 tupDesc = lookup_rowtype_tupdesc ( tupType , tupTypmod ) ;
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( tuple ) ;
 ItemPointerSetInvalid ( & ( tmptup . t_self ) ) ;
 tmptup . t_tableOid = InvalidOid ;
 tmptup . t_data = tuple ;
 result = heap_getattr ( & tmptup , attrno , tupDesc , isNull ) ;
 ReleaseTupleDesc ( tupDesc ) ;
 return result ;
 }