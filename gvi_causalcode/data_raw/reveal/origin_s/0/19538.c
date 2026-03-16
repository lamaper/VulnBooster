TEST_F ( WebFrameTest , ShowVirtualKeyboardOnElementFocus ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . InitializeRemote ( ) ;
 ShowVirtualKeyboardObserverWidgetClient web_widget_client ;
 WebLocalFrameImpl * local_frame = FrameTestHelpers : : CreateLocalChild ( * web_view_helper . RemoteMainFrame ( ) , "child" , WebFrameOwnerProperties ( ) , nullptr , nullptr , & web_widget_client ) ;
 RegisterMockedHttpURLLoad ( "input_field_default.html" ) ;
 FrameTestHelpers : : LoadFrame ( local_frame , base_url_ + "input_field_default.html" ) ;
 Frame : : NotifyUserActivation ( local_frame -> GetFrame ( ) , UserGestureToken : : kNewGesture ) ;
 local_frame -> ExecuteScript ( WebScriptSource ( "window.focus();
" "document.querySelector('input').focus();
" ) ) ;
 EXPECT_TRUE ( web_widget_client . DidShowVirtualKeyboard ( ) ) ;
 web_view_helper . Reset ( ) ;
 }