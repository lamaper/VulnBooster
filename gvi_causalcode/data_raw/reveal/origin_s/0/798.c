IN_PROC_BROWSER_TEST_F ( HostedAppTest , ShouldShowLocationBarForHostedApp ) {
 SetupApp ( "app" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.example.com/empty.html" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.example.com/blah" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "https://www.example.com/blah" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.foo.com/blah" , true ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.example.com/blah" , false ) ;
 }