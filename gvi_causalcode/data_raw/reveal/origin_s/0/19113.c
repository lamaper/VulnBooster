static Const * string_to_const ( const char * str , Oid datatype ) {
 Datum conval = string_to_datum ( str , datatype ) ;
 Oid collation ;
 int constlen ;
 switch ( datatype ) {
 case TEXTOID : case VARCHAROID : case BPCHAROID : collation = DEFAULT_COLLATION_OID ;
 constlen = - 1 ;
 break ;
 case NAMEOID : collation = InvalidOid ;
 constlen = NAMEDATALEN ;
 break ;
 case BYTEAOID : collation = InvalidOid ;
 constlen = - 1 ;
 break ;
 default : elog ( ERROR , "unexpected datatype in string_to_const: %u" , datatype ) ;
 return NULL ;
 }
 return makeConst ( datatype , - 1 , collation , constlen , conval , false , false ) ;
 }