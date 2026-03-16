IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , URLFetcherUsingExtensionContextDuringIncognitoTeardown ) {
 Browser * incognito_browser = OpenURLOffTheRecord ( browser ( ) -> profile ( ) , GURL ( "about:blank" ) ) ;
 RunURLFetcherActiveDuringIncognitoTeardownTest ( incognito_browser , incognito_browser -> profile ( ) -> GetRequestContextForExtensions ( ) ) ;
 }