int EvaluatePS ( char * str , real * stack , int size ) {
 EntityChar ec ;
 RetStack rs ;
 memset ( & ec , '\0' , sizeof ( ec ) ) ;
 memset ( & rs , '\0' , sizeof ( rs ) ) ;
 rs . max = size ;
 rs . stack = stack ;
 InterpretPS ( NULL , str , & ec , & rs ) ;
 return ( rs . cnt ) ;
 }