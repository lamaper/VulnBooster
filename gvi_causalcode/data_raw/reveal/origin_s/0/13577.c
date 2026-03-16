Const * make_greater_string ( const Const * str_const , FmgrInfo * ltproc , Oid collation ) {
 Oid datatype = str_const -> consttype ;
 char * workstr ;
 int len ;
 Datum cmpstr ;
 text * cmptxt = NULL ;
 mbcharacter_incrementer charinc ;
 if ( datatype == NAMEOID ) {
 workstr = DatumGetCString ( DirectFunctionCall1 ( nameout , str_const -> constvalue ) ) ;
 len = strlen ( workstr ) ;
 cmpstr = str_const -> constvalue ;
 }
 else if ( datatype == BYTEAOID ) {
 bytea * bstr = DatumGetByteaP ( str_const -> constvalue ) ;
 len = VARSIZE ( bstr ) - VARHDRSZ ;
 workstr = ( char * ) palloc ( len ) ;
 memcpy ( workstr , VARDATA ( bstr ) , len ) ;
 if ( ( Pointer ) bstr != DatumGetPointer ( str_const -> constvalue ) ) pfree ( bstr ) ;
 cmpstr = str_const -> constvalue ;
 }
 else {
 workstr = TextDatumGetCString ( str_const -> constvalue ) ;
 len = strlen ( workstr ) ;
 if ( lc_collate_is_c ( collation ) || len == 0 ) cmpstr = str_const -> constvalue ;
 else {
 static char suffixchar = 0 ;
 static Oid suffixcollation = 0 ;
 if ( ! suffixchar || suffixcollation != collation ) {
 char * best ;
 best = "Z" ;
 if ( varstr_cmp ( best , 1 , "z" , 1 , collation ) < 0 ) best = "z" ;
 if ( varstr_cmp ( best , 1 , "y" , 1 , collation ) < 0 ) best = "y" ;
 if ( varstr_cmp ( best , 1 , "9" , 1 , collation ) < 0 ) best = "9" ;
 suffixchar = * best ;
 suffixcollation = collation ;
 }
 cmptxt = ( text * ) palloc ( VARHDRSZ + len + 1 ) ;
 SET_VARSIZE ( cmptxt , VARHDRSZ + len + 1 ) ;
 memcpy ( VARDATA ( cmptxt ) , workstr , len ) ;
 * ( VARDATA ( cmptxt ) + len ) = suffixchar ;
 cmpstr = PointerGetDatum ( cmptxt ) ;
 }
 }
 if ( datatype == BYTEAOID ) charinc = byte_increment ;
 else charinc = pg_database_encoding_character_incrementer ( ) ;
 while ( len > 0 ) {
 int charlen ;
 unsigned char * lastchar ;
 if ( datatype == BYTEAOID ) charlen = 1 ;
 else charlen = len - pg_mbcliplen ( workstr , len , len - 1 ) ;
 lastchar = ( unsigned char * ) ( workstr + len - charlen ) ;
 while ( charinc ( lastchar , charlen ) ) {
 Const * workstr_const ;
 if ( datatype == BYTEAOID ) workstr_const = string_to_bytea_const ( workstr , len ) ;
 else workstr_const = string_to_const ( workstr , datatype ) ;
 if ( DatumGetBool ( FunctionCall2Coll ( ltproc , collation , cmpstr , workstr_const -> constvalue ) ) ) {
 if ( cmptxt ) pfree ( cmptxt ) ;
 pfree ( workstr ) ;
 return workstr_const ;
 }
 pfree ( DatumGetPointer ( workstr_const -> constvalue ) ) ;
 pfree ( workstr_const ) ;
 }
 len -= charlen ;
 workstr [ len ] = '\0' ;
 }
 if ( cmptxt ) pfree ( cmptxt ) ;
 pfree ( workstr ) ;
 return NULL ;
 }