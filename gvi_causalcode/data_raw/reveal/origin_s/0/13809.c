IN_PROC_BROWSER_TEST_F ( AvatarMenuButtonTest , MAYBE_HideOnSecondClick ) {


 CreateTestingProfile ( ) ;
 ASSERT_NO_FATAL_FAILURE ( StartAvatarMenu ( ) ) ;
 AvatarMenuButton * button = GetAvatarMenuButton ( ) ;
 static_cast < views : : MenuButtonListener * > ( button ) -> OnMenuButtonClicked ( NULL , gfx : : Point ( ) ) ;
 AvatarMenuBubbleView : : Hide ( ) ;
 base : : MessageLoop : : current ( ) -> RunUntilIdle ( ) ;
 EXPECT_FALSE ( AvatarMenuBubbleView : : IsShowing ( ) ) ;
 }