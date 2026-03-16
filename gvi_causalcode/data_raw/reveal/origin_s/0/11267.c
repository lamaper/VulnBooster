TEST_F ( WebFrameTest , ContextMenuDataSelectAll ) {
 EXPECT_FALSE ( TestSelectAll ( "<textarea></textarea>" ) ) ;
 EXPECT_TRUE ( TestSelectAll ( "<textarea>nonempty</textarea>" ) ) ;
 EXPECT_FALSE ( TestSelectAll ( "<input>" ) ) ;
 EXPECT_TRUE ( TestSelectAll ( "<input value='nonempty'>" ) ) ;
 EXPECT_FALSE ( TestSelectAll ( "<div contenteditable></div>" ) ) ;
 EXPECT_TRUE ( TestSelectAll ( "<div contenteditable>nonempty</div>" ) ) ;
 EXPECT_TRUE ( TestSelectAll ( "<div contenteditable>\n</div>" ) ) ;
 }