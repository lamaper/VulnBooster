IN_PROC_BROWSER_TEST_F ( FramebustBlockBrowserTest , ModelAllowsRedirection ) {
 const GURL blocked_urls [ ] = {
 GURL ( chrome : : kChromeUIHistoryURL ) , GURL ( chrome : : kChromeUISettingsURL ) , GURL ( chrome : : kChromeUIVersionURL ) , }
 ;
 auto * helper = GetFramebustTabHelper ( ) ;
 for ( const GURL & url : blocked_urls ) {
 helper -> AddBlockedUrl ( url , base : : BindOnce ( & FramebustBlockBrowserTest : : OnClick , base : : Unretained ( this ) ) ) ;
 }
 EXPECT_TRUE ( helper -> HasBlockedUrls ( ) ) ;
 ContentSettingFramebustBlockBubbleModel framebust_block_bubble_model ( browser ( ) -> content_setting_bubble_model_delegate ( ) , GetWebContents ( ) , browser ( ) -> profile ( ) ) ;
 EXPECT_FALSE ( clicked_index_ . has_value ( ) ) ;
 EXPECT_FALSE ( clicked_url_ . has_value ( ) ) ;
 content : : TestNavigationObserver observer ( GetWebContents ( ) ) ;
 framebust_block_bubble_model . OnListItemClicked ( 1 , ui : : EF_LEFT_MOUSE_BUTTON ) ;
 observer . Wait ( ) ;
 EXPECT_TRUE ( clicked_index_ . has_value ( ) ) ;
 EXPECT_TRUE ( clicked_url_ . has_value ( ) ) ;
 EXPECT_EQ ( 1u , clicked_index_ . value ( ) ) ;
 EXPECT_EQ ( GURL ( chrome : : kChromeUISettingsURL ) , clicked_url_ . value ( ) ) ;
 EXPECT_FALSE ( helper -> HasBlockedUrls ( ) ) ;
 EXPECT_EQ ( blocked_urls [ 1 ] , GetWebContents ( ) -> GetLastCommittedURL ( ) ) ;
 }