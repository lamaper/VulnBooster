IN_PROC_BROWSER_TEST_F ( ProfileListDesktopBrowserTest , MAYBE_SignOut ) {
 if ( ! profiles : : IsMultipleProfilesEnabled ( ) ) return ;
 ProfileManager * profile_manager = g_browser_process -> profile_manager ( ) ;
 Profile * current_profile = browser ( ) -> profile ( ) ;
 ProfileInfoCache & cache = profile_manager -> GetProfileInfoCache ( ) ;
 size_t index = cache . GetIndexOfProfileWithPath ( current_profile -> GetPath ( ) ) ;
 AvatarMenu * menu = GetAvatarMenu ( & cache ) ;
 menu -> RebuildMenu ( ) ;
 BrowserList * browser_list = BrowserList : : GetInstance ( chrome : : GetActiveDesktop ( ) ) ;
 EXPECT_EQ ( 1U , browser_list -> size ( ) ) ;
 content : : WindowedNotificationObserver window_close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : Source < Browser > ( browser ( ) ) ) ;
 EXPECT_FALSE ( cache . ProfileIsSigninRequiredAtIndex ( index ) ) ;
 profiles : : LockProfile ( current_profile ) ;
 window_close_observer . Wait ( ) ;
 EXPECT_TRUE ( cache . ProfileIsSigninRequiredAtIndex ( index ) ) ;
 EXPECT_EQ ( 0U , browser_list -> size ( ) ) ;
 chrome : : HideUserManager ( ) ;
 }