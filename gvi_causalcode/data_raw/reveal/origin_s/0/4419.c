TEST_F ( BrowsingDataRemoverImplTest , RemoveChannelIDsForServerIdentifiers ) {
 RemoveChannelIDTester tester ( GetBrowserContext ( ) ) ;
 tester . AddChannelID ( kTestRegisterableDomain1 ) ;
 tester . AddChannelID ( kTestRegisterableDomain3 ) ;
 EXPECT_EQ ( 2 , tester . ChannelIDCount ( ) ) ;
 std : : unique_ptr < BrowsingDataFilterBuilder > filter_builder ( BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : WHITELIST ) ) ;
 filter_builder -> AddRegisterableDomain ( kTestRegisterableDomain1 ) ;
 BlockUntilOriginDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_CHANNEL_IDS , std : : move ( filter_builder ) ) ;
 EXPECT_EQ ( 1 , tester . ChannelIDCount ( ) ) ;
 net : : ChannelIDStore : : ChannelIDList channel_ids ;
 tester . GetChannelIDList ( & channel_ids ) ;
 EXPECT_EQ ( kTestRegisterableDomain3 , channel_ids . front ( ) . server_identifier ( ) ) ;
 }