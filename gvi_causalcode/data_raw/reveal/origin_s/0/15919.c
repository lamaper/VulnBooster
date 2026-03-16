IN_PROC_BROWSER_TEST_F ( FramebustBlockBrowserTest , ManageButtonClicked ) {
 const GURL url = embedded_test_server ( ) -> GetURL ( "/iframe.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 auto * helper = GetFramebustTabHelper ( ) ;
 helper -> AddBlockedUrl ( url , base : : BindOnce ( & FramebustBlockBrowserTest : : OnClick , base : : Unretained ( this ) ) ) ;
 EXPECT_TRUE ( helper -> HasBlockedUrls ( ) ) ;
 ContentSettingFramebustBlockBubbleModel framebust_block_bubble_model ( browser ( ) -> content_setting_bubble_model_delegate ( ) , GetWebContents ( ) , browser ( ) -> profile ( ) ) ;
 content : : TestNavigationObserver navigation_observer ( nullptr ) ;
 navigation_observer . StartWatchingNewWebContents ( ) ;
 framebust_block_bubble_model . OnManageButtonClicked ( ) ;
 navigation_observer . Wait ( ) ;
 EXPECT_TRUE ( base : : StartsWith ( navigation_observer . last_navigation_url ( ) . spec ( ) , chrome : : kChromeUISettingsURL , base : : CompareCase : : SENSITIVE ) ) ;
 }