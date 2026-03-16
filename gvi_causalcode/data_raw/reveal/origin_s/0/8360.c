TEST_F ( BrowsingDataRemoverImplTest , RemoveChannelIDLastHour ) {
 RemoveChannelIDTester tester ( GetBrowserContext ( ) ) ;
 base : : Time now = base : : Time : : Now ( ) ;
 tester . AddChannelID ( kTestOrigin1 ) ;
 tester . AddChannelIDWithTimes ( kTestOrigin2 , now - base : : TimeDelta : : FromHours ( 2 ) ) ;
 EXPECT_EQ ( 0 , tester . ssl_config_changed_count ( ) ) ;
 EXPECT_EQ ( 2 , tester . ChannelIDCount ( ) ) ;
 BlockUntilBrowsingDataRemoved ( AnHourAgo ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_CHANNEL_IDS , false ) ;
 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_CHANNEL_IDS , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 EXPECT_EQ ( 1 , tester . ssl_config_changed_count ( ) ) ;
 ASSERT_EQ ( 1 , tester . ChannelIDCount ( ) ) ;
 net : : ChannelIDStore : : ChannelIDList channel_ids ;
 tester . GetChannelIDList ( & channel_ids ) ;
 ASSERT_EQ ( 1U , channel_ids . size ( ) ) ;
 EXPECT_EQ ( kTestOrigin2 , channel_ids . front ( ) . server_identifier ( ) ) ;
 }