TEST_F ( BrowsingDataRemoverImplTest , RemoveChannelIDForever ) {
 RemoveChannelIDTester tester ( GetBrowserContext ( ) ) ;
 tester . AddChannelID ( kTestOrigin1 ) ;
 EXPECT_EQ ( 0 , tester . ssl_config_changed_count ( ) ) ;
 EXPECT_EQ ( 1 , tester . ChannelIDCount ( ) ) ;
 BlockUntilBrowsingDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_CHANNEL_IDS , false ) ;
 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_CHANNEL_IDS , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 EXPECT_EQ ( 1 , tester . ssl_config_changed_count ( ) ) ;
 EXPECT_EQ ( 0 , tester . ChannelIDCount ( ) ) ;
 }