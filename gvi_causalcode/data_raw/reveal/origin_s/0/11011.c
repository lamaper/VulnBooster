TEST_F ( BrowsingDataRemoverImplTest , RemoveCookiesDomainBlacklist ) {
 std : : unique_ptr < BrowsingDataFilterBuilder > filter ( BrowsingDataFilterBuilder : : Create ( BrowsingDataFilterBuilder : : BLACKLIST ) ) ;
 filter -> AddRegisterableDomain ( kTestRegisterableDomain1 ) ;
 filter -> AddRegisterableDomain ( kTestRegisterableDomain3 ) ;
 BlockUntilOriginDataRemoved ( AnHourAgo ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_COOKIES , std : : move ( filter ) ) ;
 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_COOKIES , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 StoragePartitionRemovalData removal_data = GetStoragePartitionRemovalData ( ) ;
 EXPECT_EQ ( removal_data . remove_mask , StoragePartition : : REMOVE_DATA_MASK_COOKIES ) ;
 EXPECT_EQ ( removal_data . quota_storage_remove_mask , ~ StoragePartition : : QUOTA_MANAGED_STORAGE_MASK_PERSISTENT ) ;
 EXPECT_EQ ( removal_data . remove_begin , GetBeginTime ( ) ) ;
 EXPECT_FALSE ( removal_data . origin_matcher . Run ( kOrigin1 , mock_policy ( ) ) ) ;
 EXPECT_TRUE ( removal_data . origin_matcher . Run ( kOrigin2 , mock_policy ( ) ) ) ;
 EXPECT_FALSE ( removal_data . origin_matcher . Run ( kOrigin3 , mock_policy ( ) ) ) ;
 EXPECT_FALSE ( removal_data . origin_matcher . Run ( kOrigin4 , mock_policy ( ) ) ) ;
 EXPECT_FALSE ( removal_data . cookie_matcher . Run ( CreateCookieWithHost ( kOrigin1 ) ) ) ;
 EXPECT_TRUE ( removal_data . cookie_matcher . Run ( CreateCookieWithHost ( kOrigin2 ) ) ) ;
 EXPECT_FALSE ( removal_data . cookie_matcher . Run ( CreateCookieWithHost ( kOrigin3 ) ) ) ;
 EXPECT_FALSE ( removal_data . cookie_matcher . Run ( CreateCookieWithHost ( kOrigin4 ) ) ) ;
 }