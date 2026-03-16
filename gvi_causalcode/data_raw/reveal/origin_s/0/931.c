TEST_F ( ShortcutsBackendTest , EntitySuggestionTest ) {
 SetSearchProvider ( ) ;
 AutocompleteMatch match ;
 match . fill_into_edit = base : : UTF8ToUTF16 ( "franklin d roosevelt" ) ;
 match . type = AutocompleteMatchType : : SEARCH_SUGGEST_ENTITY ;
 match . contents = base : : UTF8ToUTF16 ( "roosevelt" ) ;
 match . contents_class = AutocompleteMatch : : ClassificationsFromString ( "0,0,5,2" ) ;
 match . description = base : : UTF8ToUTF16 ( "Franklin D. Roosevelt" ) ;
 match . description_class = AutocompleteMatch : : ClassificationsFromString ( "0,4" ) ;
 match . destination_url = GURL ( "http://www.foo.com/search?bar=franklin+d+roosevelt&gs_ssp=1234" ) ;
 match . keyword = base : : UTF8ToUTF16 ( "foo" ) ;
 match . search_terms_args . reset ( new TemplateURLRef : : SearchTermsArgs ( match . fill_into_edit ) ) ;
 SearchTermsData search_terms_data ;
 ShortcutsDatabase : : Shortcut : : MatchCore match_core = ShortcutsBackend : : MatchToMatchCore ( match , GetTemplateURLService ( ) , & search_terms_data ) ;
 EXPECT_EQ ( "http://foo.com/search?bar=franklin+d+roosevelt" , match_core . destination_url . spec ( ) ) ;
 EXPECT_EQ ( match . fill_into_edit , match_core . contents ) ;
 EXPECT_EQ ( "0,0" , match_core . contents_class ) ;
 EXPECT_EQ ( base : : string16 ( ) , match_core . description ) ;
 EXPECT_TRUE ( match_core . description_class . empty ( ) ) ;
 }