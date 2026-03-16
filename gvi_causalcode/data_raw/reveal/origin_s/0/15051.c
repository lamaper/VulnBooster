TEST_F ( TemplateURLTest , Defaults ) {
 TemplateURLData data ;
 EXPECT_FALSE ( data . show_in_default_list ) ;
 EXPECT_FALSE ( data . safe_for_autoreplace ) ;
 EXPECT_EQ ( 0 , data . prepopulate_id ) ;
 }