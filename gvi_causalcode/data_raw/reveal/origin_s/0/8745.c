IN_PROC_BROWSER_TEST_F ( HostedAppTest , ShouldShowLocationBarForHTTPSBookmarkApp ) {
 base : : CommandLine : : ForCurrentProcess ( ) -> AppendSwitch ( switches : : kEnableNewBookmarkApps ) ;
 SetupApp ( "https_app" , true ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "https://www.example.com/empty.html" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "https://www.example.com/blah" , false ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.example.com/blah" , true ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "http://www.foo.com/blah" , true ) ;
 NavigateAndCheckForLocationBar ( app_browser_ , "https://www.example.com/blah" , false ) ;
 }