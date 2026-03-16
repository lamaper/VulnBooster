void xsltFreeLocales ( void ) {

 xmlFree ( xsltLocaleList ) ;
 xsltLocaleList = NULL ;
 xmlRMutexUnlock ( xsltLocaleMutex ) ;
