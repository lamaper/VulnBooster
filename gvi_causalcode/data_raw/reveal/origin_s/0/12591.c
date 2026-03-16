static CURLcode glob_fixed ( URLGlob * glob , char * fixed , size_t len ) {
 URLPattern * pat = & glob -> pattern [ glob -> size ] ;
 pat -> type = UPTSet ;
 pat -> content . Set . size = 1 ;
 pat -> content . Set . ptr_s = 0 ;
 pat -> globindex = - 1 ;
 pat -> content . Set . elements = malloc ( sizeof ( char * ) ) ;
 if ( ! pat -> content . Set . elements ) return GLOBERROR ( "out of memory" , 0 , CURLE_OUT_OF_MEMORY ) ;
 pat -> content . Set . elements [ 0 ] = malloc ( len + 1 ) ;
 if ( ! pat -> content . Set . elements [ 0 ] ) return GLOBERROR ( "out of memory" , 0 , CURLE_OUT_OF_MEMORY ) ;
 memcpy ( pat -> content . Set . elements [ 0 ] , fixed , len ) ;
 pat -> content . Set . elements [ 0 ] [ len ] = 0 ;
 return CURLE_OK ;
 }