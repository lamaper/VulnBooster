IN_PROC_BROWSER_TEST_P ( SupervisedUserNavigationThrottleTest , NoNavigationObserverBlock ) {
 Profile * profile = browser ( ) -> profile ( ) ;
 SupervisedUserSettingsService * supervised_user_settings_service = SupervisedUserSettingsServiceFactory : : GetForProfile ( profile ) ;
 supervised_user_settings_service -> SetLocalSetting ( supervised_users : : kContentPackDefaultFilteringBehavior , std : : unique_ptr < base : : Value > ( new base : : Value ( SupervisedUserURLFilter : : BLOCK ) ) ) ;
 std : : unique_ptr < WebContents > web_contents ( WebContents : : Create ( WebContents : : CreateParams ( profile ) ) ) ;
 NavigationController & controller = web_contents -> GetController ( ) ;
 content : : TestNavigationObserver observer ( web_contents . get ( ) ) ;
 controller . LoadURL ( GURL ( "http://www.example.com" ) , content : : Referrer ( ) , ui : : PAGE_TRANSITION_TYPED , std : : string ( ) ) ;
 observer . Wait ( ) ;
 content : : NavigationEntry * entry = controller . GetActiveEntry ( ) ;
 ASSERT_TRUE ( entry ) ;
 EXPECT_EQ ( content : : PAGE_TYPE_NORMAL , entry -> GetPageType ( ) ) ;
 EXPECT_FALSE ( observer . last_navigation_succeeded ( ) ) ;
 }