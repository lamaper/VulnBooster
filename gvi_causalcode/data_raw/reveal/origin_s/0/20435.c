TEST_F ( ImmersiveModeControllerAshTest , TabAndBrowserFullscreen ) {
 AddTab ( browser ( ) , GURL ( "about:blank" ) ) ;
 ash : : ShelfLayoutManager * shelf = ash : : Shell : : GetPrimaryRootWindowController ( ) -> GetShelfLayoutManager ( ) ;
 ASSERT_EQ ( ash : : SHELF_VISIBLE , shelf -> visibility_state ( ) ) ;
 ToggleFullscreen ( ) ;
 ASSERT_TRUE ( controller ( ) -> IsEnabled ( ) ) ;
 EXPECT_EQ ( ash : : SHELF_AUTO_HIDE , shelf -> visibility_state ( ) ) ;
 EXPECT_FALSE ( controller ( ) -> ShouldHideTabIndicators ( ) ) ;
 SetTabFullscreen ( true ) ;
 ASSERT_TRUE ( controller ( ) -> IsEnabled ( ) ) ;
 EXPECT_EQ ( ash : : SHELF_HIDDEN , shelf -> visibility_state ( ) ) ;
 EXPECT_TRUE ( controller ( ) -> ShouldHideTabIndicators ( ) ) ;
 SetTabFullscreen ( false ) ;
 ASSERT_TRUE ( controller ( ) -> IsEnabled ( ) ) ;
 EXPECT_EQ ( ash : : SHELF_AUTO_HIDE , shelf -> visibility_state ( ) ) ;
 EXPECT_FALSE ( controller ( ) -> ShouldHideTabIndicators ( ) ) ;
 SetTabFullscreen ( true ) ;
 ToggleFullscreen ( ) ;
 ASSERT_FALSE ( controller ( ) -> IsEnabled ( ) ) ;
 EXPECT_EQ ( ash : : SHELF_VISIBLE , shelf -> visibility_state ( ) ) ;
 EXPECT_TRUE ( controller ( ) -> ShouldHideTabIndicators ( ) ) ;
 }