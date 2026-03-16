static void tupledesc_match ( TupleDesc dst_tupdesc , TupleDesc src_tupdesc ) {
 int i ;
 if ( dst_tupdesc -> natts != src_tupdesc -> natts ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "function return row and query-specified return row do not match" ) , errdetail_plural ( "Returned row contains %d attribute, but query expects %d." , "Returned row contains %d attributes, but query expects %d." , src_tupdesc -> natts , src_tupdesc -> natts , dst_tupdesc -> natts ) ) ) ;
 for ( i = 0 ;
 i < dst_tupdesc -> natts ;
 i ++ ) {
 Form_pg_attribute dattr = dst_tupdesc -> attrs [ i ] ;
 Form_pg_attribute sattr = src_tupdesc -> attrs [ i ] ;
 if ( IsBinaryCoercible ( sattr -> atttypid , dattr -> atttypid ) ) continue ;
 if ( ! dattr -> attisdropped ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "function return row and query-specified return row do not match" ) , errdetail ( "Returned type %s at ordinal position %d, but query expects %s." , format_type_be ( sattr -> atttypid ) , i + 1 , format_type_be ( dattr -> atttypid ) ) ) ) ;
 if ( dattr -> attlen != sattr -> attlen || dattr -> attalign != sattr -> attalign ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "function return row and query-specified return row do not match" ) , errdetail ( "Physical storage mismatch on dropped attribute at ordinal position %d." , i + 1 ) ) ) ;
 }
 }