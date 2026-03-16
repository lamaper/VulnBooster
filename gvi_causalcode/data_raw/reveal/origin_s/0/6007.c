TEST_F ( BrowsingDataRemoverImplTest , RemoveUnprotectedLocalStorageForever ) {

 policy -> AddProtected ( kOrigin1 . GetOrigin ( ) ) ;

 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_LOCAL_STORAGE , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 StoragePartitionRemovalData removal_data = GetStoragePartitionRemovalData ( ) ;
 EXPECT_EQ ( removal_data . remove_mask , StoragePartition : : REMOVE_DATA_MASK_LOCAL_STORAGE ) ;
 EXPECT_EQ ( removal_data . quota_storage_remove_mask , StoragePartition : : QUOTA_MANAGED_STORAGE_MASK_ALL ) ;
 EXPECT_EQ ( removal_data . remove_begin , GetBeginTime ( ) ) ;
 EXPECT_EQ ( ShouldRemoveForProtectedOriginOne ( ) , removal_data . origin_matcher . Run ( kOrigin1 , mock_policy ( ) ) ) ;
 EXPECT_TRUE ( removal_data . origin_matcher . Run ( kOrigin2 , mock_policy ( ) ) ) ;
 EXPECT_TRUE ( removal_data . origin_matcher . Run ( kOrigin3 , mock_policy ( ) ) ) ;
 EXPECT_FALSE ( removal_data . origin_matcher . Run ( kOriginExt , mock_policy ( ) ) ) ;
 }