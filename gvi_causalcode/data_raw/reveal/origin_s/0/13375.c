bool TestSelectAll ( const std : : string & html ) {
 ContextMenuWebFrameClient frame ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 WebViewImpl * web_view = web_view_helper . Initialize ( & frame ) ;
 FrameTestHelpers : : LoadHTMLString ( web_view -> MainFrameImpl ( ) , html , ToKURL ( "about:blank" ) ) ;
 web_view -> Resize ( WebSize ( 500 , 300 ) ) ;
 web_view -> UpdateAllLifecyclePhases ( ) ;
 RunPendingTasks ( ) ;
 web_view -> SetInitialFocus ( false ) ;
 RunPendingTasks ( ) ;
 WebMouseEvent mouse_event ( WebInputEvent : : kMouseDown , WebInputEvent : : kNoModifiers , WebInputEvent : : GetStaticTimeStampForTests ( ) ) ;
 mouse_event . button = WebMouseEvent : : Button : : kRight ;
 mouse_event . SetPositionInWidget ( 8 , 8 ) ;
 mouse_event . click_count = 1 ;
 web_view -> HandleInputEvent ( WebCoalescedInputEvent ( mouse_event ) ) ;
 RunPendingTasks ( ) ;
 web_view_helper . Reset ( ) ;
 return frame . GetMenuData ( ) . edit_flags & WebContextMenuData : : kCanSelectAll ;
 }