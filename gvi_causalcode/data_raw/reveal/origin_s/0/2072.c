TEST_F ( IconLabelBubbleViewTest , MouseInkDropState ) {
 AttachInkDrop ( ) ;
 generator ( ) -> PressLeftButton ( ) ;
 EXPECT_EQ ( views : : InkDropState : : ACTION_PENDING , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 generator ( ) -> ReleaseLeftButton ( ) ;
 EXPECT_EQ ( views : : InkDropState : : ACTIVATED , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 view ( ) -> HideBubble ( ) ;
 EXPECT_EQ ( views : : InkDropState : : HIDDEN , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 generator ( ) -> PressLeftButton ( ) ;
 EXPECT_EQ ( views : : InkDropState : : ACTION_PENDING , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 generator ( ) -> ReleaseLeftButton ( ) ;
 EXPECT_EQ ( views : : InkDropState : : ACTIVATED , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 generator ( ) -> PressLeftButton ( ) ;
 EXPECT_NE ( views : : InkDropState : : ACTION_PENDING , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 }