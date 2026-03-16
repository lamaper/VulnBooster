IN_PROC_BROWSER_TEST_F ( FullscreenControllerTest , PendingMouseLockExitsOnTabSwitch ) {
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 WebContents * tab1 = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 RequestToLockMouse ( true , false ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 browser ( ) -> tab_strip_model ( ) -> ActivateTabAt ( 0 , true ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 {
 MouseLockNotificationObserver mouse_lock_observer ;
 browser ( ) -> tab_strip_model ( ) -> ActivateTabAt ( 1 , true ) ;
 mouse_lock_observer . Wait ( ) ;
 }
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 RequestToLockMouse ( true , false ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 chrome : : CloseWebContents ( browser ( ) , tab1 , false ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 }