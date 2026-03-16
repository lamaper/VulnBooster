SplinePointList * SplinePointListInterpretPS ( FILE * ps , int flags , int is_stroked , int * width ) {
 EntityChar ec ;
 SplineChar sc ;
 memset ( & ec , '\0' , sizeof ( ec ) ) ;
 ec . width = ec . vwidth = UNDEFINED_WIDTH ;
 memset ( & sc , 0 , sizeof ( sc ) ) ;
 sc . name = "<No particular character>" ;
 ec . sc = & sc ;
 InterpretPS ( ps , NULL , & ec , NULL ) ;
 if ( width != NULL ) * width = ec . width ;
 return ( SplinesFromEntityChar ( & ec , & flags , is_stroked ) ) ;
 }