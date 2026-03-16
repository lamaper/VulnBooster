static StemInfo * HintNew ( double start , double width ) {
 StemInfo * h ;
 h = chunkalloc ( sizeof ( StemInfo ) ) ;
 h -> start = start ;
 h -> width = width ;
 return ( h ) ;
 }