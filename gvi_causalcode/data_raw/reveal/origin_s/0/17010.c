static void xml_cdata ( void * userData , const XML_Char * s , int len ) {
 struct xml_ctx * ctx = ( struct xml_ctx * ) userData ;
 free ( ctx -> cdata ) ;
 ctx -> cdata = xmemdupz ( s , len ) ;
 }