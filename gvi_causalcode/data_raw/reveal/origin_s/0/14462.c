IN_PROC_BROWSER_TEST_F ( NewAvatarMenuButtonTest , MAYBE_SignOut ) {
 if ( ! profiles : : IsMultipleProfilesEnabled ( ) ) return ;
 CreateTestingProfile ( ) ;
 ASSERT_NO_FATAL_FAILURE ( StartAvatarMenu ( ) ) ;
 BrowserList * browser_list = BrowserList : : GetInstance ( chrome : : GetActiveDesktop ( ) ) ;
 EXPECT_EQ ( 1U , browser_list -> size ( ) ) ;
 content : : WindowedNotificationObserver window_close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : Source < Browser > ( browser ( ) ) ) ;
 AvatarMenu * menu = ProfileChooserView : : profile_bubble_ -> avatar_menu_ . get ( ) ;
 const AvatarMenu : : Item & menu_item_before = menu -> GetItemAt ( menu -> GetActiveProfileIndex ( ) ) ;
 EXPECT_FALSE ( menu_item_before . signin_required ) ;
 ui : : MouseEvent mouse_ev ( ui : : ET_MOUSE_RELEASED , gfx : : Point ( ) , gfx : : Point ( ) , 0 , 0 ) ;
 ProfileChooserView : : profile_bubble_ -> ButtonPressed ( ProfileChooserView : : profile_bubble_ -> lock_button_ , mouse_ev ) ;
 EXPECT_TRUE ( menu -> GetItemAt ( menu -> GetActiveProfileIndex ( ) ) . signin_required ) ;
 window_close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_list -> empty ( ) ) ;
 if ( ! UserManager : : IsShowing ( ) ) base : : MessageLoop : : current ( ) -> RunUntilIdle ( ) ;
 UserManager : : Hide ( ) ;
 }