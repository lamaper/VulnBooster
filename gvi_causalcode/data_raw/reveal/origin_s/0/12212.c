TEST_F ( WebFrameTest , NavigatorPluginsClearedWhenPluginsDisabled ) {
 ScopedFakePluginRegistry fake_plugins ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . Initialize ( ) ;
 v8 : : HandleScope scope ( v8 : : Isolate : : GetCurrent ( ) ) ;
 v8 : : Local < v8 : : Value > result = web_view_helper . LocalMainFrame ( ) -> ExecuteScriptAndReturnValue ( WebScriptSource ( "navigator.plugins.length" ) ) ;
 EXPECT_NE ( 0 , result -> Int32Value ( ) ) ;
 web_view_helper . GetWebView ( ) -> GetPage ( ) -> GetSettings ( ) . SetPluginsEnabled ( false ) ;
 result = web_view_helper . LocalMainFrame ( ) -> ExecuteScriptAndReturnValue ( WebScriptSource ( "navigator.plugins.length" ) ) ;
 EXPECT_EQ ( 0 , result -> Int32Value ( ) ) ;
 }