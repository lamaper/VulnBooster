IN_PROC_BROWSER_TEST_F ( SitePerProcessAutofillTest , PasswordAutofillPopupPositionInsideOOPIF ) {
 SetupMainTab ( ) ;
 ASSERT_TRUE ( base : : FeatureList : : IsEnabled ( security_state : : kHttpFormWarningFeature ) ) ;
 GURL main_url ( embedded_test_server ( ) -> GetURL ( "a.com" , "/iframe.html" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , main_url ) ;
 content : : WebContents * active_web_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 ASSERT_TRUE ( content : : ExecuteScript ( active_web_contents , base : : StringPrintf ( "var iframe = document.querySelector('iframe');
" "iframe.style.marginTop = '%dpx';
" "iframe.style.marginLeft = '%dpx';
" , kIframeTopDisplacement , kIframeLeftDisplacement ) ) ) ;
 GURL frame_url = embedded_test_server ( ) -> GetURL ( "b.com" , "/title1.html" ) ;
 EXPECT_TRUE ( NavigateIframeToURL ( active_web_contents , "test" , frame_url ) ) ;
 content : : RenderFrameHost * child_frame = content : : FrameMatchingPredicate ( active_web_contents , base : : Bind ( & content : : FrameIsChildOfMainFrame ) ) ;
 FocusedEditableNodeChangedObserver focus_observer ;
 ASSERT_TRUE ( ExecuteScript ( child_frame , "window.focus();
" "var input = document.createElement('input');
" "input.type = 'password';
" "document.body.appendChild(input);
" "input.focus();
" ) ) ;
 focus_observer . WaitForFocusChangeInPage ( ) ;
 content : : SimulateKeyPress ( active_web_contents , ui : : DomKey : : FromCharacter ( 'A' ) , ui : : DomCode : : US_A , ui : : VKEY_A , false , false , false , false ) ;
 autofill_client ( ) . WaitForNextPopup ( ) ;
 gfx : : Point bounds_origin ( static_cast < int > ( autofill_client ( ) . last_element_bounds ( ) . origin ( ) . x ( ) ) , static_cast < int > ( autofill_client ( ) . last_element_bounds ( ) . origin ( ) . y ( ) ) ) ;
 bounds_origin += active_web_contents -> GetRenderWidgetHostView ( ) -> GetViewBounds ( ) . OffsetFromOrigin ( ) ;
 gfx : : Vector2d error = bounds_origin - focus_observer . focused_node_bounds_in_screen ( ) ;
 EXPECT_LT ( error . Length ( ) , 1.4143f ) << "Origin of bounds from focused node changed event is '" << focus_observer . focused_node_bounds_in_screen ( ) . ToString ( ) << "' but AutofillClient is reporting '" << bounds_origin . ToString ( ) << "'" ;
 }