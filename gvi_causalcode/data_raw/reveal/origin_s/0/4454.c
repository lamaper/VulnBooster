static char * convert_string_datum ( Datum value , Oid typid ) {
 char * val ;
 switch ( typid ) {
 case CHAROID : val = ( char * ) palloc ( 2 ) ;
 val [ 0 ] = DatumGetChar ( value ) ;
 val [ 1 ] = '\0' ;
 break ;
 case BPCHAROID : case VARCHAROID : case TEXTOID : val = TextDatumGetCString ( value ) ;
 break ;
 case NAMEOID : {
 NameData * nm = ( NameData * ) DatumGetPointer ( value ) ;
 val = pstrdup ( NameStr ( * nm ) ) ;
 break ;
 }
 default : elog ( ERROR , "unsupported type: %u" , typid ) ;
 return NULL ;
 }
 if ( ! lc_collate_is_c ( DEFAULT_COLLATION_OID ) ) {
 char * xfrmstr ;
 size_t xfrmlen ;
 size_t xfrmlen2 PG_USED_FOR_ASSERTS_ONLY ;

 char x [ 1 ] ;
 xfrmlen = strxfrm ( x , val , 0 ) ;
 }



 xfrmlen2 = strxfrm ( xfrmstr , val , xfrmlen + 1 ) ;
 Assert ( xfrmlen2 <= xfrmlen ) ;
 pfree ( val ) ;
 val = xfrmstr ;
 }
 return val ;
 }