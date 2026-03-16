IN_PROC_BROWSER_TEST_F ( SitePerProcessInteractivePDFTest , ContextMenuPositionForEmbeddedPDFInCrossOriginFrame ) {
 GURL main_url ( embedded_test_server ( ) -> GetURL ( "a.com" , "/iframe.html" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , main_url ) ;
 EXPECT_EQ ( 0U , test_guest_view_manager ( ) -> num_guests_created ( ) ) ;
 content : : WebContents * active_web_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 EXPECT_TRUE ( ExecuteScript ( active_web_contents , "document.querySelector('iframe').style =" " 'margin-left: 100px;
 margin-top: 100px;
';
" ) ) ;
 GURL frame_url = embedded_test_server ( ) -> GetURL ( "b.com" , "/page_with_embedded_pdf.html" ) ;
 EXPECT_TRUE ( NavigateIframeToURL ( active_web_contents , "test" , frame_url ) ) ;
 content : : WebContents * guest_contents = test_guest_view_manager ( ) -> WaitForSingleGuestCreated ( ) ;
 NavigationToExtensionSchemeObserver navigation_observer ( guest_contents ) ;
 navigation_observer . Wait ( ) ;
 content : : RenderWidgetHostView * child_view = ChildFrameAt ( active_web_contents -> GetMainFrame ( ) , 0 ) -> GetView ( ) ;
 ContextMenuWaiter menu_waiter ( content : : NotificationService : : AllSources ( ) ) ;
 auto send_right_mouse_event = [ ] ( content : : RenderWidgetHost * host , int x , int y , blink : : WebInputEvent : : Type type ) {
 blink : : WebMouseEvent event ;
 event . x = x ;
 event . y = y ;
 event . button = blink : : WebMouseEvent : : Button : : Right ;
 event . setType ( type ) ;
 host -> ForwardMouseEvent ( event ) ;
 }
 ;
 send_right_mouse_event ( child_view -> GetRenderWidgetHost ( ) , 10 , 20 , blink : : WebInputEvent : : MouseDown ) ;
 send_right_mouse_event ( child_view -> GetRenderWidgetHost ( ) , 10 , 20 , blink : : WebInputEvent : : MouseUp ) ;
 menu_waiter . WaitForMenuOpenAndClose ( ) ;
 gfx : : Point point_in_root_window = child_view -> TransformPointToRootCoordSpace ( gfx : : Point ( 10 , 20 ) ) ;
 EXPECT_EQ ( point_in_root_window . x ( ) , menu_waiter . params ( ) . x ) ;
 EXPECT_EQ ( point_in_root_window . y ( ) , menu_waiter . params ( ) . y ) ;
 }