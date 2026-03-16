IN_PROC_BROWSER_TEST_F ( MimeHandlerViewTest , ResizeBeforeAttach ) {
 TestMimeHandlerViewGuest : : DelayNextCreateWebContents ( 500 ) ;
 RunTest ( "test_resize_before_attach.html" ) ;
 content : : WebContents * guest_web_contents = GetGuestViewManager ( ) -> WaitForSingleGuestCreated ( ) ;
 TestMimeHandlerViewGuest * guest = static_cast < TestMimeHandlerViewGuest * > ( MimeHandlerViewGuest : : FromWebContents ( guest_web_contents ) ) ;
 guest -> WaitForGuestAttached ( ) ;
 auto guest_size = guest -> size ( ) ;
 CHECK_EQ ( guest_size . width ( ) , 500 ) ;
 CHECK_EQ ( guest_size . height ( ) , 400 ) ;
 }