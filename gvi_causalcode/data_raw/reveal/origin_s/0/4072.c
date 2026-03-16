TEST_F ( OmniboxViewViewsTest , OnBlur ) {
 int kOmniboxWidth = 60 ;
 gfx : : RenderText * render_text = omnibox_view ( ) -> GetRenderText ( ) ;
 render_text -> SetDisplayRect ( gfx : : Rect ( 0 , 0 , kOmniboxWidth , 10 ) ) ;
 render_text -> SetHorizontalAlignment ( gfx : : ALIGN_LEFT ) ;
 omnibox_view ( ) -> OnFocus ( ) ;
 const base : : string16 kContentsRtl = base : : WideToUTF16 ( L"\x05e8\x05e2.\x05e7\x05d5\x05dd/0123/abcd" ) ;
 static_cast < OmniboxView * > ( omnibox_view ( ) ) -> SetWindowTextAndCaretPos ( kContentsRtl , 0 , false , false ) ;
 EXPECT_EQ ( gfx : : NO_ELIDE , render_text -> elide_behavior ( ) ) ;
 EXPECT_GT ( 0 , render_text -> GetUpdatedDisplayOffset ( ) . x ( ) ) ;
 omnibox_view ( ) -> OnBlur ( ) ;
 EXPECT_EQ ( gfx : : ELIDE_TAIL , render_text -> elide_behavior ( ) ) ;
 EXPECT_EQ ( 0 , render_text -> GetUpdatedDisplayOffset ( ) . x ( ) ) ;
 }