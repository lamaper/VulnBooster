void xmlInitializeGlobalState ( xmlGlobalStatePtr gs ) {


 xmlMutexLock ( xmlThrDefMutex ) ;



 gs -> xmlBufferAllocScheme = xmlBufferAllocSchemeThrDef ;
 gs -> xmlDefaultBufferSize = xmlDefaultBufferSizeThrDef ;


 gs -> xmlDefaultSAXLocator . getSystemId = xmlSAX2GetSystemId ;
 gs -> xmlDefaultSAXLocator . getLineNumber = xmlSAX2GetLineNumber ;
 gs -> xmlDefaultSAXLocator . getColumnNumber = xmlSAX2GetColumnNumber ;
 gs -> xmlDoValidityCheckingDefaultValue = xmlDoValidityCheckingDefaultValueThrDef ;

 gs -> xmlMalloc = ( xmlMallocFunc ) xmlMemMalloc ;
 gs -> xmlMallocAtomic = ( xmlMallocFunc ) xmlMemMalloc ;
 gs -> xmlRealloc = ( xmlReallocFunc ) xmlMemRealloc ;
 gs -> xmlMemStrdup = ( xmlStrdupFunc ) xmlMemoryStrdup ;

 gs -> xmlMalloc = ( xmlMallocFunc ) malloc ;
 gs -> xmlMallocAtomic = ( xmlMallocFunc ) malloc ;
 gs -> xmlRealloc = ( xmlReallocFunc ) realloc ;
 gs -> xmlMemStrdup = ( xmlStrdupFunc ) xmlStrdup ;

 gs -> xmlIndentTreeOutput = xmlIndentTreeOutputThrDef ;
 gs -> xmlTreeIndentString = xmlTreeIndentStringThrDef ;
 gs -> xmlKeepBlanksDefaultValue = xmlKeepBlanksDefaultValueThrDef ;
 gs -> xmlLineNumbersDefaultValue = xmlLineNumbersDefaultValueThrDef ;
 gs -> xmlLoadExtDtdDefaultValue = xmlLoadExtDtdDefaultValueThrDef ;
 gs -> xmlParserDebugEntities = xmlParserDebugEntitiesThrDef ;
 gs -> xmlParserVersion = LIBXML_VERSION_STRING ;
 gs -> xmlPedanticParserDefaultValue = xmlPedanticParserDefaultValueThrDef ;
 gs -> xmlSaveNoEmptyTags = xmlSaveNoEmptyTagsThrDef ;
 gs -> xmlSubstituteEntitiesDefaultValue = xmlSubstituteEntitiesDefaultValueThrDef ;
 gs -> xmlGenericError = xmlGenericErrorThrDef ;
 gs -> xmlStructuredError = xmlStructuredErrorThrDef ;
 gs -> xmlGenericErrorContext = xmlGenericErrorContextThrDef ;
 gs -> xmlStructuredErrorContext = xmlStructuredErrorContextThrDef ;
 gs -> xmlRegisterNodeDefaultValue = xmlRegisterNodeDefaultValueThrDef ;
 gs -> xmlDeregisterNodeDefaultValue = xmlDeregisterNodeDefaultValueThrDef ;
 gs -> xmlParserInputBufferCreateFilenameValue = xmlParserInputBufferCreateFilenameValueThrDef ;
 gs -> xmlOutputBufferCreateFilenameValue = xmlOutputBufferCreateFilenameValueThrDef ;
 memset ( & gs -> xmlLastError , 0 , sizeof ( xmlError ) ) ;
 xmlMutexUnlock ( xmlThrDefMutex ) ;
 }