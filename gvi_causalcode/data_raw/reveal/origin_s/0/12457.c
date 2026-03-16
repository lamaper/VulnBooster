IN_PROC_BROWSER_TEST_F ( AppApiTest , SameBrowsingInstanceAfterSwap ) {
 extensions : : ProcessMap * process_map = extensions : : ProcessMap : : Get ( browser ( ) -> profile ( ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 const Extension * app = LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ;
 ASSERT_TRUE ( app ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path1/iframe.html" ) ) ;
 content : : SiteInstance * app_instance = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) -> GetSiteInstance ( ) ;
 EXPECT_TRUE ( process_map -> Contains ( app_instance -> GetProcess ( ) -> GetID ( ) ) ) ;
 const BrowserList * active_browser_list = BrowserList : : GetInstance ( ) ;
 EXPECT_EQ ( 2U , active_browser_list -> size ( ) ) ;
 content : : WebContents * popup_contents = active_browser_list -> get ( 1 ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 content : : WaitForLoadStop ( popup_contents ) ;
 SiteInstance * popup_instance = popup_contents -> GetSiteInstance ( ) ;
 EXPECT_EQ ( app_instance , popup_instance ) ;
 GURL non_app_url ( base_url . Resolve ( "path3/empty.html" ) ) ;
 ui_test_utils : : NavigateToURL ( active_browser_list -> get ( 1 ) , non_app_url ) ;
 SiteInstance * new_instance = popup_contents -> GetSiteInstance ( ) ;
 EXPECT_NE ( app_instance , new_instance ) ;
 EXPECT_TRUE ( app_instance -> IsRelatedSiteInstance ( new_instance ) ) ;
 }