TEST_F ( ImmersiveModeControllerAshTest , ExitUponRestore ) {
 ASSERT_FALSE ( controller ( ) -> IsEnabled ( ) ) ;
 ToggleFullscreen ( ) ;
 AttemptReveal ( ) ;
 ASSERT_TRUE ( controller ( ) -> IsEnabled ( ) ) ;
 ASSERT_TRUE ( controller ( ) -> IsRevealed ( ) ) ;
 ASSERT_TRUE ( browser_view ( ) -> GetWidget ( ) -> IsFullscreen ( ) ) ;
 browser_view ( ) -> GetWidget ( ) -> Restore ( ) ;
 EXPECT_FALSE ( controller ( ) -> IsEnabled ( ) ) ;
 }