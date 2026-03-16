TEST_F ( TemplateURLTest , ExtractSearchTermsFromNonUTF8URL ) {
 TemplateURLData data ;
 data . SetURL ( "http://windows-1251.ru/?q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://windows-1251.ru/#q={
searchTerms}
" ) ;
 data . alternate_urls . push_back ( "http://windows-1251.ru/path/{
searchTerms}
" ) ;
 data . input_encodings . push_back ( "windows-1251" ) ;
 TemplateURL url ( data ) ;
 base : : string16 result ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://windows-1251.ru/?q=%C7%E4%F0%E0%E2%F1%F2%E2%F3%E9%2C+" "%EC%E8%F0!" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : WideToUTF16 ( L"\x0417\x0434\x0440\x0430\x0432\x0441\x0442\x0432\x0443\x0439, " L"\x043C\x0438\x0440!" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://windows-1251.ru/#q=%E4%E2%E0+%F1%EB%EE%E2%E0" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : WideToUTF16 ( L"\x0434\x0432\x0430 \x0441\x043B\x043E\x0432\x0430" ) , result ) ;
 EXPECT_TRUE ( url . ExtractSearchTermsFromURL ( GURL ( "http://windows-1251.ru/path/%E1%F3%EA%E2%FB%20%C0%20%E8%20A" ) , search_terms_data_ , & result ) ) ;
 EXPECT_EQ ( base : : WideToUTF16 ( L"\x0431\x0443\x043A\x0432\x044B \x0410 \x0438 A" ) , result ) ;
 }