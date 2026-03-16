static Pattern_Prefix_Status like_fixed_prefix ( Const * patt_const , bool case_insensitive , Oid collation , Const * * prefix_const , Selectivity * rest_selec ) {
 char * match ;
 char * patt ;
 int pattlen ;
 Oid typeid = patt_const -> consttype ;
 int pos , match_pos ;
 bool is_multibyte = ( pg_database_encoding_max_length ( ) > 1 ) ;
 pg_locale_t locale = 0 ;
 bool locale_is_c = false ;
 Assert ( typeid == BYTEAOID || typeid == TEXTOID ) ;
 if ( case_insensitive ) {
 if ( typeid == BYTEAOID ) ereport ( ERROR , ( errcode ( ERRCODE_FEATURE_NOT_SUPPORTED ) , errmsg ( "case insensitive matching not supported on type bytea" ) ) ) ;
 if ( lc_ctype_is_c ( collation ) ) locale_is_c = true ;
 else if ( collation != DEFAULT_COLLATION_OID ) {
 if ( ! OidIsValid ( collation ) ) {
 ereport ( ERROR , ( errcode ( ERRCODE_INDETERMINATE_COLLATION ) , errmsg ( "could not determine which collation to use for ILIKE" ) , errhint ( "Use the COLLATE clause to set the collation explicitly." ) ) ) ;
 }
 locale = pg_newlocale_from_collation ( collation ) ;
 }
 }
 if ( typeid != BYTEAOID ) {
 patt = TextDatumGetCString ( patt_const -> constvalue ) ;
 pattlen = strlen ( patt ) ;
 }
 else {
 bytea * bstr = DatumGetByteaP ( patt_const -> constvalue ) ;
 pattlen = VARSIZE ( bstr ) - VARHDRSZ ;
 patt = ( char * ) palloc ( pattlen ) ;
 memcpy ( patt , VARDATA ( bstr ) , pattlen ) ;
 if ( ( Pointer ) bstr != DatumGetPointer ( patt_const -> constvalue ) ) pfree ( bstr ) ;
 }
 match = palloc ( pattlen + 1 ) ;
 match_pos = 0 ;
 for ( pos = 0 ;
 pos < pattlen ;
 pos ++ ) {
 if ( patt [ pos ] == '%' || patt [ pos ] == '_' ) break ;
 if ( patt [ pos ] == '\\' ) {
 pos ++ ;
 if ( pos >= pattlen ) break ;
 }
 if ( case_insensitive && pattern_char_isalpha ( patt [ pos ] , is_multibyte , locale , locale_is_c ) ) break ;
 match [ match_pos ++ ] = patt [ pos ] ;
 }
 match [ match_pos ] = '\0' ;
 if ( typeid != BYTEAOID ) * prefix_const = string_to_const ( match , typeid ) ;
 else * prefix_const = string_to_bytea_const ( match , match_pos ) ;
 if ( rest_selec != NULL ) * rest_selec = like_selectivity ( & patt [ pos ] , pattlen - pos , case_insensitive ) ;
 pfree ( patt ) ;
 pfree ( match ) ;
 if ( pos == pattlen ) return Pattern_Prefix_Exact ;
 if ( match_pos > 0 ) return Pattern_Prefix_Partial ;
 return Pattern_Prefix_None ;
 }