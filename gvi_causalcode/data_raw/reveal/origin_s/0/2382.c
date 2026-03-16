TEST_F ( WebFrameTest , ContextMenuDataNonLocatedMenu ) {
 ContextMenuWebFrameClient frame ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 WebViewImpl * web_view = web_view_helper . Initialize ( & frame ) ;
 const std : : string & html = "<div style='font-size: 1000%;
 line-height: 0.7em'>Select me<br/>" "Next line</div>" ;
 FrameTestHelpers : : LoadHTMLString ( web_view -> MainFrameImpl ( ) , html , ToKURL ( "about:blank" ) ) ;
 web_view -> Resize ( WebSize ( 500 , 300 ) ) ;
 web_view -> UpdateAllLifecyclePhases ( ) ;
 RunPendingTasks ( ) ;
 web_view -> SetInitialFocus ( false ) ;
 RunPendingTasks ( ) ;
 WebMouseEvent mouse_event ( WebInputEvent : : kMouseDown , WebInputEvent : : kNoModifiers , WebInputEvent : : GetStaticTimeStampForTests ( ) ) ;
 mouse_event . button = WebMouseEvent : : Button : : kLeft ;
 mouse_event . SetPositionInWidget ( 0 , 0 ) ;
 mouse_event . click_count = 2 ;
 web_view -> HandleInputEvent ( WebCoalescedInputEvent ( mouse_event ) ) ;
 web_view -> ShowContextMenu ( kMenuSourceTouch ) ;
 RunPendingTasks ( ) ;
 web_view_helper . Reset ( ) ;
 EXPECT_EQ ( frame . GetMenuData ( ) . source_type , kMenuSourceTouch ) ;
 EXPECT_FALSE ( frame . GetMenuData ( ) . selected_text . IsEmpty ( ) ) ;
 }