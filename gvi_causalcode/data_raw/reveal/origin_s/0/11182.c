IN_PROC_BROWSER_TEST_F ( FramebustBlockBrowserTest , DisallowRadioButtonSelected ) {
 const GURL url = embedded_test_server ( ) -> GetURL ( "/iframe.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 auto * helper = GetFramebustTabHelper ( ) ;
 helper -> AddBlockedUrl ( url , base : : BindOnce ( & FramebustBlockBrowserTest : : OnClick , base : : Unretained ( this ) ) ) ;
 EXPECT_TRUE ( helper -> HasBlockedUrls ( ) ) ;
 HostContentSettingsMap * settings_map = HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 EXPECT_EQ ( CONTENT_SETTING_BLOCK , settings_map -> GetContentSetting ( url , GURL ( ) , CONTENT_SETTINGS_TYPE_POPUPS , std : : string ( ) ) ) ;
 {
 ContentSettingFramebustBlockBubbleModel framebust_block_bubble_model ( browser ( ) -> content_setting_bubble_model_delegate ( ) , GetWebContents ( ) , browser ( ) -> profile ( ) ) ;
 framebust_block_bubble_model . OnRadioClicked ( kDisallowRadioButtonIndex ) ;
 }
 EXPECT_EQ ( CONTENT_SETTING_BLOCK , settings_map -> GetContentSetting ( url , GURL ( ) , CONTENT_SETTINGS_TYPE_POPUPS , std : : string ( ) ) ) ;
 }