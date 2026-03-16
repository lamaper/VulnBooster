static xsltAttrVTPtr xsltSetAttrVTsegment ( xsltAttrVTPtr avt , void * val ) {
 if ( avt -> nb_seg >= avt -> max_seg ) {
 avt = ( xsltAttrVTPtr ) xmlRealloc ( avt , sizeof ( xsltAttrVT ) + avt -> max_seg * sizeof ( void * ) ) ;
 if ( avt == NULL ) {
 return NULL ;
 }
 memset ( & avt -> segments [ avt -> nb_seg ] , 0 , MAX_AVT_SEG * sizeof ( void * ) ) ;
 avt -> max_seg += MAX_AVT_SEG ;
 }
 avt -> segments [ avt -> nb_seg ++ ] = val ;
 return avt ;
 }