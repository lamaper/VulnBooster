TEST_F ( IconLabelBubbleViewTest , SecondClick ) {
 generator ( ) -> PressLeftButton ( ) ;
 EXPECT_FALSE ( view ( ) -> IsBubbleShowing ( ) ) ;
 generator ( ) -> ReleaseLeftButton ( ) ;
 EXPECT_TRUE ( view ( ) -> IsBubbleShowing ( ) ) ;
 generator ( ) -> PressLeftButton ( ) ;
 view ( ) -> HideBubble ( ) ;
 EXPECT_FALSE ( view ( ) -> IsBubbleShowing ( ) ) ;
 generator ( ) -> ReleaseLeftButton ( ) ;
 }