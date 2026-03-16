SplinePointList * SplinesFromEntities ( Entity * ent , int * flags , int is_stroked ) {
 EntityChar ec ;
 memset ( & ec , '\0' , sizeof ( ec ) ) ;
 ec . splines = ent ;
 return ( SplinesFromEntityChar ( & ec , flags , is_stroked ) ) ;
 }