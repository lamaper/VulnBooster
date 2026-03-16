IN_PROC_BROWSER_TEST_F ( ProfileListDesktopBrowserTest , MAYBE_SwitchToProfile ) {


 ProfileManager * profile_manager = g_browser_process -> profile_manager ( ) ;
 Profile * current_profile = browser ( ) -> profile ( ) ;
 ProfileInfoCache & cache = profile_manager -> GetProfileInfoCache ( ) ;
 base : : FilePath path_profile1 = current_profile -> GetPath ( ) ;
 base : : FilePath user_dir = cache . GetUserDataDir ( ) ;
 base : : FilePath path_profile2 = user_dir . Append ( FILE_PATH_LITERAL ( "New Profile 2" ) ) ;
 profile_manager -> CreateProfileAsync ( path_profile2 , base : : Bind ( & OnUnblockOnProfileCreation ) , base : : string16 ( ) , base : : string16 ( ) , std : : string ( ) ) ;
 content : : RunMessageLoop ( ) ;
 ASSERT_EQ ( cache . GetNumberOfProfiles ( ) , 2U ) ;
 AvatarMenu * menu = GetAvatarMenu ( & cache ) ;
 menu -> RebuildMenu ( ) ;
 BrowserList * browser_list = BrowserList : : GetInstance ( chrome : : GetActiveDesktop ( ) ) ;
 EXPECT_EQ ( 1U , browser_list -> size ( ) ) ;
 EXPECT_EQ ( path_profile1 , browser_list -> get ( 0 ) -> profile ( ) -> GetPath ( ) ) ;
 menu -> SwitchToProfile ( cache . GetIndexOfProfileWithPath ( path_profile1 ) , false , ProfileMetrics : : SWITCH_PROFILE_ICON ) ;
 EXPECT_EQ ( 1U , browser_list -> size ( ) ) ;
 EXPECT_EQ ( path_profile1 , browser_list -> get ( 0 ) -> profile ( ) -> GetPath ( ) ) ;
 menu -> SwitchToProfile ( cache . GetIndexOfProfileWithPath ( path_profile2 ) , false , ProfileMetrics : : SWITCH_PROFILE_ICON ) ;
 EXPECT_EQ ( 2U , browser_list -> size ( ) ) ;
 menu -> SwitchToProfile ( cache . GetIndexOfProfileWithPath ( path_profile1 ) , false , ProfileMetrics : : SWITCH_PROFILE_ICON ) ;
 EXPECT_EQ ( 2U , browser_list -> size ( ) ) ;
 EXPECT_EQ ( path_profile1 , browser_list -> get ( 0 ) -> profile ( ) -> GetPath ( ) ) ;
 EXPECT_EQ ( path_profile2 , browser_list -> get ( 1 ) -> profile ( ) -> GetPath ( ) ) ;
 }