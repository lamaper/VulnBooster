Entity * EntityInterpretPS ( FILE * ps , int * width ) {
 EntityChar ec ;
 memset ( & ec , '\0' , sizeof ( ec ) ) ;
 ec . width = ec . vwidth = UNDEFINED_WIDTH ;
 InterpretPS ( ps , NULL , & ec , NULL ) ;
 if ( width != NULL ) * width = ec . width ;
 return ( ec . splines ) ;
 }