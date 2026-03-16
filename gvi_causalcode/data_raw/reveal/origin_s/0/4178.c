void exsltCommonRegister ( void ) {
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "node-set" , EXSLT_COMMON_NAMESPACE , exsltNodeSetFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "object-type" , EXSLT_COMMON_NAMESPACE , exsltObjectTypeFunction ) ;
 xsltRegisterExtModuleElement ( ( const xmlChar * ) "document" , EXSLT_COMMON_NAMESPACE , ( xsltPreComputeFunction ) xsltDocumentComp , ( xsltTransformFunction ) xsltDocumentElem ) ;
 }