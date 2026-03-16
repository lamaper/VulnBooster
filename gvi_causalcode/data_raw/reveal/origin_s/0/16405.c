static ulong get_access ( TABLE * form , uint fieldnr , uint * next_field ) {
 ulong access_bits = 0 , bit ;
 char buff [ 2 ] ;
 String res ( buff , sizeof ( buff ) , & my_charset_latin1 ) ;
 Field * * pos ;
 for ( pos = form -> field + fieldnr , bit = 1 ;
 * pos && ( * pos ) -> real_type ( ) == MYSQL_TYPE_ENUM && ( ( Field_enum * ) ( * pos ) ) -> typelib -> count == 2 ;
 pos ++ , fieldnr ++ , bit <<= 1 ) {
 ( * pos ) -> val_str ( & res ) ;
 if ( my_toupper ( & my_charset_latin1 , res [ 0 ] ) == 'Y' ) access_bits |= bit ;
 }
 if ( next_field ) * next_field = fieldnr ;
 return access_bits ;
 }