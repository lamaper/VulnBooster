TEST_F ( ScoredHistoryMatchTest , CullSearchResults ) {
 scoped_ptr < TemplateURLService > template_url_service = make_scoped_ptr ( new TemplateURLService ( nullptr , make_scoped_ptr ( new SearchTermsData ) , nullptr , scoped_ptr < TemplateURLServiceClient > ( ) , nullptr , nullptr , base : : Closure ( ) ) ) ;
 base : : Time now = base : : Time : : NowFromSystemTime ( ) ;
 history : : URLRow row ( MakeURLRow ( "http://testsearch.com/thequery" , "Test Search Engine" , 3 , 30 , 1 ) ) ;
 RowWordStarts word_starts ;
 PopulateWordStarts ( row , & word_starts ) ;
 WordStarts one_word_no_offset ( 1 , 0u ) ;
 VisitInfoVector visits = CreateVisitInfoVector ( 3 , 30 , now ) ;
 visits [ 0 ] . second = ui : : PAGE_TRANSITION_TYPED ;
 ScoredHistoryMatch scored_a ( row , visits , ASCIIToUTF16 ( "thequery" ) , Make1Term ( "thequery" ) , one_word_no_offset , word_starts , false , template_url_service . get ( ) , now ) ;
 EXPECT_GT ( scored_a . raw_score , 0 ) ;
 ScoredHistoryMatch scored_b ( row , visits , ASCIIToUTF16 ( "testsearch" ) , Make1Term ( "testsearch" ) , one_word_no_offset , word_starts , false , template_url_service . get ( ) , now ) ;
 EXPECT_GT ( scored_b . raw_score , 0 ) ;
 TemplateURLData data ;
 data . SetShortName ( ASCIIToUTF16 ( "TestEngine" ) ) ;
 data . SetKeyword ( ASCIIToUTF16 ( "TestEngine" ) ) ;
 data . SetURL ( "http://testsearch.com/{
searchTerms}
" ) ;
 TemplateURL * template_url = new TemplateURL ( data ) ;
 template_url_service -> Add ( template_url ) ;
 template_url_service -> SetUserSelectedDefaultSearchProvider ( template_url ) ;
 template_url_service -> Load ( ) ;
 ScoredHistoryMatch scored_c ( row , visits , ASCIIToUTF16 ( "thequery" ) , Make1Term ( "thequery" ) , one_word_no_offset , word_starts , false , template_url_service . get ( ) , now ) ;
 EXPECT_EQ ( 0 , scored_c . raw_score ) ;
 ScoredHistoryMatch scored_d ( row , visits , ASCIIToUTF16 ( "testsearch" ) , Make1Term ( "testsearch" ) , one_word_no_offset , word_starts , false , template_url_service . get ( ) , now ) ;
 EXPECT_EQ ( 0 , scored_d . raw_score ) ;
 }