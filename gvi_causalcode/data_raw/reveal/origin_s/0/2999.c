IN_PROC_BROWSER_TEST_F ( FramebustBlockBrowserTest , FramebustAllowedByGlobalSetting ) {
 HostContentSettingsMap * settings_map = HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 settings_map -> SetDefaultContentSetting ( ContentSettingsType : : CONTENT_SETTINGS_TYPE_POPUPS , CONTENT_SETTING_ALLOW ) ;
 CreateAndSetBrowser ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/iframe.html" ) ) ;
 NavigateIframeToUrlWithoutGesture ( GetWebContents ( ) , "test" , embedded_test_server ( ) -> GetURL ( "a.com" , "/title1.html" ) ) ;
 content : : RenderFrameHost * child = content : : ChildFrameAt ( GetWebContents ( ) -> GetMainFrame ( ) , 0 ) ;
 ASSERT_TRUE ( child ) ;
 GURL redirect_url = embedded_test_server ( ) -> GetURL ( "b.com" , "/title1.html" ) ;
 content : : TestNavigationObserver observer ( GetWebContents ( ) ) ;
 child -> ExecuteJavaScriptForTests ( base : : ASCIIToUTF16 ( base : : StringPrintf ( "window.top.location = '%s';
" , redirect_url . spec ( ) . c_str ( ) ) ) ) ;
 observer . Wait ( ) ;
 EXPECT_TRUE ( GetFramebustTabHelper ( ) -> blocked_urls ( ) . empty ( ) ) ;
 }