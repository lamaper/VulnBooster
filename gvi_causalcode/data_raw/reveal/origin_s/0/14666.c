TEST_F ( IconLabelBubbleViewTest , GestureInkDropState ) {
 AttachInkDrop ( ) ;
 generator ( ) -> GestureTapAt ( gfx : : Point ( ) ) ;
 EXPECT_EQ ( views : : InkDropState : : ACTIVATED , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 view ( ) -> HideBubble ( ) ;
 EXPECT_EQ ( views : : InkDropState : : HIDDEN , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 generator ( ) -> GestureTapAt ( gfx : : Point ( ) ) ;
 EXPECT_EQ ( views : : InkDropState : : ACTIVATED , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 generator ( ) -> GestureTapAt ( gfx : : Point ( ) ) ;
 view ( ) -> HideBubble ( ) ;
 EXPECT_EQ ( views : : InkDropState : : HIDDEN , ink_drop ( ) -> GetTargetInkDropState ( ) ) ;
 }