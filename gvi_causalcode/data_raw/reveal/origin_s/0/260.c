IN_PROC_BROWSER_TEST_F ( AppApiTest , NavigateIntoAppProcess ) {
 extensions : : ProcessMap * process_map = extensions : : ProcessMap : : Get ( browser ( ) -> profile ( ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 LOG ( INFO ) << "Loading path1/empty.html." ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/empty.html" ) ) ;
 LOG ( INFO ) << "Loading path1/empty.html - done." ;
 WebContents * contents = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) ;
 EXPECT_FALSE ( process_map -> Contains ( contents -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 LOG ( INFO ) << "Loading extension." ;
 const Extension * app = LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ;
 LOG ( INFO ) << "Loading extension - done." ;
 ASSERT_TRUE ( app ) ;
 LOG ( INFO ) << "Loading path1/empty.html." ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/empty.html" ) ) ;
 LOG ( INFO ) << "Loading path1/empty.html - done." ;
 EXPECT_TRUE ( process_map -> Contains ( contents -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 LOG ( INFO ) << "Disabling extension." ;
 DisableExtension ( app -> id ( ) ) ;
 LOG ( INFO ) << "Disabling extension - done." ;
 LOG ( INFO ) << "Loading path1/empty.html." ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/empty.html" ) ) ;
 LOG ( INFO ) << "Loading path1/empty.html - done." ;
 EXPECT_FALSE ( process_map -> Contains ( contents -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 }