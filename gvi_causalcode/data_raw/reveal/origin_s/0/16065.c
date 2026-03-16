IN_PROC_BROWSER_TEST_F ( AppApiTest , OpenWebPopupFromWebIframe ) {
 extensions : : ProcessMap * process_map = extensions : : ProcessMap : : Get ( browser ( ) -> profile ( ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 const Extension * app = LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ;
 ASSERT_TRUE ( app ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/container.html" ) ) ;
 content : : RenderProcessHost * process = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) -> GetRenderProcessHost ( ) ;
 EXPECT_TRUE ( process_map -> Contains ( process -> GetID ( ) ) ) ;
 const BrowserList * active_browser_list = BrowserList : : GetInstance ( ) ;
 EXPECT_EQ ( 2U , active_browser_list -> size ( ) ) ;
 content : : WebContents * popup_contents = active_browser_list -> get ( 1 ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 content : : WaitForLoadStop ( popup_contents ) ;
 bool should_be_in_same_process = ! content : : AreAllSitesIsolatedForTesting ( ) ;
 content : : RenderProcessHost * popup_process = popup_contents -> GetRenderProcessHost ( ) ;
 EXPECT_EQ ( should_be_in_same_process , process == popup_process ) ;
 EXPECT_EQ ( should_be_in_same_process , process_map -> Contains ( popup_process -> GetID ( ) ) ) ;
 }