IN_PROC_BROWSER_TEST_F ( AppApiTest , MAYBE_ReloadAppAfterCrash ) {
 extensions : : ProcessMap * process_map = extensions : : ProcessMap : : Get ( browser ( ) -> profile ( ) ) ;
 ASSERT_TRUE ( LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/empty.html" ) ) ;
 WebContents * contents = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) ;
 EXPECT_TRUE ( process_map -> Contains ( contents -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 bool is_installed = false ;
 ASSERT_TRUE ( content : : ExecuteScriptAndExtractBool ( contents , "window.domAutomationController.send(chrome.app.isInstalled)" , & is_installed ) ) ;
 ASSERT_TRUE ( is_installed ) ;
 content : : CrashTab ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ) ;
 content : : WindowedNotificationObserver observer ( content : : NOTIFICATION_LOAD_STOP , content : : Source < NavigationController > ( & browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetController ( ) ) ) ;
 chrome : : Reload ( browser ( ) , WindowOpenDisposition : : CURRENT_TAB ) ;
 observer . Wait ( ) ;
 ASSERT_TRUE ( content : : ExecuteScriptAndExtractBool ( contents , "window.domAutomationController.send(chrome.app.isInstalled)" , & is_installed ) ) ;
 ASSERT_TRUE ( is_installed ) ;
 }