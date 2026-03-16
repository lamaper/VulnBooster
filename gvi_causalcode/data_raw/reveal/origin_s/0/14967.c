IN_PROC_BROWSER_TEST_F ( AppApiTest , DISABLED_AppProcessRedirectBack ) {
 ASSERT_TRUE ( LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 chrome : : NewTab ( browser ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/empty.html" ) ) ;
 chrome : : NewTab ( browser ( ) ) ;
 ui_test_utils : : NavigateToURLBlockUntilNavigationsComplete ( browser ( ) , base_url . Resolve ( "path1/redirect.html" ) , 2 ) ;
 ASSERT_EQ ( 3 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( "/extensions/api_test/app_process/path1/empty.html" , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetController ( ) . GetLastCommittedEntry ( ) -> GetURL ( ) . path ( ) ) ;
 EXPECT_EQ ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> GetRenderProcessHost ( ) , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetRenderProcessHost ( ) ) ;
 }