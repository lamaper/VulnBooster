IN_PROC_BROWSER_TEST_F ( FullscreenControllerTest , PendingMouseLockExitsOnTabClose ) {
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 RequestToLockMouse ( true , false ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 {
 MouseLockNotificationObserver mouse_lock_observer ;
 chrome : : CloseTab ( browser ( ) ) ;
 mouse_lock_observer . Wait ( ) ;
 }
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 }