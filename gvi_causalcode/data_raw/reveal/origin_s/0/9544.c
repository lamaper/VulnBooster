IN_PROC_BROWSER_TEST_F ( HostedAppTest , LocationBarForHostedAppWithoutWWW ) {
 SetupApp ( "app_no_www" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://example.com/empty.html" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.example.com/empty.html" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.foo.com/blah" , true ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://example.com/blah" , false ) ;
 }