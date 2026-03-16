TEST_F ( WebFrameTest , ContextMenuDataSelectedText ) {
 ContextMenuWebFrameClient frame ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 WebViewImpl * web_view = web_view_helper . Initialize ( & frame ) ;
 const std : : string & html = "<input value=' '>" ;
 FrameTestHelpers : : LoadHTMLString ( web_view -> MainFrameImpl ( ) , html , ToKURL ( "about:blank" ) ) ;
 web_view -> Resize ( WebSize ( 500 , 300 ) ) ;
 web_view -> UpdateAllLifecyclePhases ( ) ;
 RunPendingTasks ( ) ;
 web_view -> SetInitialFocus ( false ) ;
 RunPendingTasks ( ) ;
 web_view -> MainFrameImpl ( ) -> ExecuteCommand ( WebString : : FromUTF8 ( "SelectAll" ) ) ;
 WebMouseEvent mouse_event ( WebInputEvent : : kMouseDown , WebInputEvent : : kNoModifiers , WebInputEvent : : GetStaticTimeStampForTests ( ) ) ;
 mouse_event . button = WebMouseEvent : : Button : : kRight ;
 mouse_event . SetPositionInWidget ( 8 , 8 ) ;
 mouse_event . click_count = 1 ;
 web_view -> HandleInputEvent ( WebCoalescedInputEvent ( mouse_event ) ) ;
 RunPendingTasks ( ) ;
 web_view_helper . Reset ( ) ;
 EXPECT_EQ ( frame . GetMenuData ( ) . selected_text , " " ) ;
 }