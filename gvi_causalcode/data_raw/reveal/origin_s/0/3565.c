static Const * string_to_bytea_const ( const char * str , size_t str_len ) {
 bytea * bstr = palloc ( VARHDRSZ + str_len ) ;
 Datum conval ;
 memcpy ( VARDATA ( bstr ) , str , str_len ) ;
 SET_VARSIZE ( bstr , VARHDRSZ + str_len ) ;
 conval = PointerGetDatum ( bstr ) ;
 return makeConst ( BYTEAOID , - 1 , InvalidOid , - 1 , conval , false , false ) ;
 }