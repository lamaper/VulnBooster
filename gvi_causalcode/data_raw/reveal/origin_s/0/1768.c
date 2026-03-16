static void GenerateHash ( const std : : string & input , std : : string * output ) {
 if ( input . empty ( ) ) {
 * output = "" ;
 return ;
 }
 uint8_t hash [ 4 ] ;
 crypto : : SHA256HashString ( input , hash , sizeof ( hash ) ) ;
 * output = base : : ToLowerASCII ( base : : HexEncode ( hash , sizeof ( hash ) ) ) ;
 }