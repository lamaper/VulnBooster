static double convert_numeric_to_scalar ( Datum value , Oid typid ) {
 switch ( typid ) {
 case BOOLOID : return ( double ) DatumGetBool ( value ) ;
 case INT2OID : return ( double ) DatumGetInt16 ( value ) ;
 case INT4OID : return ( double ) DatumGetInt32 ( value ) ;
 case INT8OID : return ( double ) DatumGetInt64 ( value ) ;
 case FLOAT4OID : return ( double ) DatumGetFloat4 ( value ) ;
 case FLOAT8OID : return ( double ) DatumGetFloat8 ( value ) ;
 case NUMERICOID : return ( double ) DatumGetFloat8 ( DirectFunctionCall1 ( numeric_float8_no_overflow , value ) ) ;
 case OIDOID : case REGPROCOID : case REGPROCEDUREOID : case REGOPEROID : case REGOPERATOROID : case REGCLASSOID : case REGTYPEOID : case REGCONFIGOID : case REGDICTIONARYOID : case REGROLEOID : case REGNAMESPACEOID : return ( double ) DatumGetObjectId ( value ) ;
 }
 elog ( ERROR , "unsupported type: %u" , typid ) ;
 return 0 ;
 }