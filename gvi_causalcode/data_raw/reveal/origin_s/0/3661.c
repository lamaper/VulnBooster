static Pattern_Prefix_Status regex_fixed_prefix ( Const * patt_const , bool case_insensitive , Oid collation , Const * * prefix_const , Selectivity * rest_selec ) {
 Oid typeid = patt_const -> consttype ;
 char * prefix ;
 bool exact ;
 if ( typeid == BYTEAOID ) ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "regular-expression matching not supported on type bytea" ) ) ) ;
 prefix = regexp_fixed_prefix ( DatumGetTextPP ( patt_const -> constvalue ) , case_insensitive , collation , & exact ) ;
 if ( prefix == NULL ) {
 * prefix_const = NULL ;
 if ( rest_selec != NULL ) {
 char * patt = TextDatumGetCString ( patt_const -> constvalue ) ;
 * rest_selec = regex_selectivity ( patt , strlen ( patt ) , case_insensitive , 0 ) ;
 pfree ( patt ) ;
 }
 return Pattern_Prefix_None ;
 }
 * prefix_const = string_to_const ( prefix , typeid ) ;
 if ( rest_selec != NULL ) {
 if ( exact ) {
 * rest_selec = 1.0 ;
 }
 else {
 char * patt = TextDatumGetCString ( patt_const -> constvalue ) ;
 * rest_selec = regex_selectivity ( patt , strlen ( patt ) , case_insensitive , strlen ( prefix ) ) ;
 pfree ( patt ) ;
 }
 }
 pfree ( prefix ) ;
 if ( exact ) return Pattern_Prefix_Exact ;
 else return Pattern_Prefix_Partial ;
 }