TEST_F ( ImmersiveModeControllerAshTest , EnabledCommands ) {
 ASSERT_FALSE ( controller ( ) -> IsEnabled ( ) ) ;
 EXPECT_TRUE ( chrome : : IsCommandEnabled ( browser ( ) , IDC_OPEN_CURRENT_URL ) ) ;
 EXPECT_TRUE ( chrome : : IsCommandEnabled ( browser ( ) , IDC_ABOUT ) ) ;
 EXPECT_TRUE ( chrome : : IsCommandEnabled ( browser ( ) , IDC_FOCUS_LOCATION ) ) ;
 ToggleFullscreen ( ) ;
 EXPECT_TRUE ( controller ( ) -> IsEnabled ( ) ) ;
 EXPECT_TRUE ( chrome : : IsCommandEnabled ( browser ( ) , IDC_OPEN_CURRENT_URL ) ) ;
 EXPECT_TRUE ( chrome : : IsCommandEnabled ( browser ( ) , IDC_ABOUT ) ) ;
 EXPECT_TRUE ( chrome : : IsCommandEnabled ( browser ( ) , IDC_FOCUS_LOCATION ) ) ;
 }