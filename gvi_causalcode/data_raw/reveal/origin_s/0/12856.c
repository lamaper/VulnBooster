IN_PROC_BROWSER_TEST_F ( AppApiTest , OpenAppFromIframe ) {
 extensions : : ProcessMap * process_map = extensions : : ProcessMap : : Get ( browser ( ) -> profile ( ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 const Extension * app = LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ;
 ASSERT_TRUE ( app ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path3/container.html" ) ) ;
 EXPECT_FALSE ( process_map -> Contains ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 const BrowserList * active_browser_list = BrowserList : : GetInstance ( ) ;
 EXPECT_EQ ( 2U , active_browser_list -> size ( ) ) ;
 content : : WebContents * popup_contents = active_browser_list -> get ( 1 ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 content : : WaitForLoadStop ( popup_contents ) ;
 RenderViewHost * popup_host = popup_contents -> GetRenderViewHost ( ) ;
 EXPECT_TRUE ( process_map -> Contains ( popup_host -> GetProcess ( ) -> GetID ( ) ) ) ;
 }