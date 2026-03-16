static bool convert_to_scalar ( Datum value , Oid valuetypid , double * scaledvalue , Datum lobound , Datum hibound , Oid boundstypid , double * scaledlobound , double * scaledhibound ) {
 switch ( valuetypid ) {
 case BOOLOID : case INT2OID : case INT4OID : case INT8OID : case FLOAT4OID : case FLOAT8OID : case NUMERICOID : case OIDOID : case REGPROCOID : case REGPROCEDUREOID : case REGOPEROID : case REGOPERATOROID : case REGCLASSOID : case REGTYPEOID : case REGCONFIGOID : case REGDICTIONARYOID : case REGROLEOID : case REGNAMESPACEOID : * scaledvalue = convert_numeric_to_scalar ( value , valuetypid ) ;
 * scaledlobound = convert_numeric_to_scalar ( lobound , boundstypid ) ;
 * scaledhibound = convert_numeric_to_scalar ( hibound , boundstypid ) ;
 return true ;
 case CHAROID : case BPCHAROID : case VARCHAROID : case TEXTOID : case NAMEOID : {
 char * valstr = convert_string_datum ( value , valuetypid ) ;
 char * lostr = convert_string_datum ( lobound , boundstypid ) ;
 char * histr = convert_string_datum ( hibound , boundstypid ) ;
 convert_string_to_scalar ( valstr , scaledvalue , lostr , scaledlobound , histr , scaledhibound ) ;
 pfree ( valstr ) ;
 pfree ( lostr ) ;
 pfree ( histr ) ;
 return true ;
 }
 case BYTEAOID : {
 convert_bytea_to_scalar ( value , scaledvalue , lobound , scaledlobound , hibound , scaledhibound ) ;
 return true ;
 }
 case TIMESTAMPOID : case TIMESTAMPTZOID : case ABSTIMEOID : case DATEOID : case INTERVALOID : case RELTIMEOID : case TINTERVALOID : case TIMEOID : case TIMETZOID : * scaledvalue = convert_timevalue_to_scalar ( value , valuetypid ) ;
 * scaledlobound = convert_timevalue_to_scalar ( lobound , boundstypid ) ;
 * scaledhibound = convert_timevalue_to_scalar ( hibound , boundstypid ) ;
 return true ;
 case INETOID : case CIDROID : case MACADDROID : * scaledvalue = convert_network_to_scalar ( value , valuetypid ) ;
 * scaledlobound = convert_network_to_scalar ( lobound , boundstypid ) ;
 * scaledhibound = convert_network_to_scalar ( hibound , boundstypid ) ;
 return true ;
 }
 * scaledvalue = * scaledlobound = * scaledhibound = 0 ;
 return false ;
 }