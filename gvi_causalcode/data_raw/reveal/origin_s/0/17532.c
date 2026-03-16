IN_PROC_BROWSER_TEST_F ( AppApiTest , ClientRedirectToAppFromExtension ) {
 LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ;
 const Extension * launcher = LoadExtension ( test_data_dir_ . AppendASCII ( "app_launcher" ) ) ;
 content : : TestNavigationObserver test_navigation_observer ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , 3 ) ;
 test_navigation_observer . StartWatchingNewWebContents ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , launcher -> GetResourceURL ( "client_redirect.html" ) ) ;
 test_navigation_observer . Wait ( ) ;
 bool is_installed = false ;
 ASSERT_TRUE ( content : : ExecuteScriptAndExtractBool ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , "window.domAutomationController.send(chrome.app.isInstalled)" , & is_installed ) ) ;
 ASSERT_TRUE ( is_installed ) ;
 }