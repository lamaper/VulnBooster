void appendByteaLiteral ( PQExpBuffer buf , const unsigned char * str , size_t length , bool std_strings ) {
 const unsigned char * source = str ;
 char * target ;
 static const char hextbl [ ] = "0123456789abcdef" ;
 if ( ! enlargePQExpBuffer ( buf , 2 * length + 5 ) ) return ;
 target = buf -> data + buf -> len ;
 * target ++ = '\'' ;
 if ( ! std_strings ) * target ++ = '\\' ;
 * target ++ = '\\' ;
 * target ++ = 'x' ;
 while ( length -- > 0 ) {
 unsigned char c = * source ++ ;
 * target ++ = hextbl [ ( c >> 4 ) & 0xF ] ;
 * target ++ = hextbl [ c & 0xF ] ;
 }
 * target ++ = '\'' ;
 * target = '\0' ;
 buf -> len = target - buf -> data ;
 }