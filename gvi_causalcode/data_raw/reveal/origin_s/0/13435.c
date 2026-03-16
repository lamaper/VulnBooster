TEST_F ( BrowsingDataRemoverImplTest , RemoveCookieForever ) {
 BlockUntilBrowsingDataRemoved ( base : : Time ( ) , base : : Time : : Max ( ) , BrowsingDataRemover : : REMOVE_COOKIES , false ) ;
 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_COOKIES , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 StoragePartitionRemovalData removal_data = GetStoragePartitionRemovalData ( ) ;
 EXPECT_EQ ( removal_data . remove_mask , StoragePartition : : REMOVE_DATA_MASK_COOKIES ) ;
 EXPECT_EQ ( removal_data . quota_storage_remove_mask , StoragePartition : : QUOTA_MANAGED_STORAGE_MASK_ALL ) ;
 EXPECT_EQ ( removal_data . remove_begin , GetBeginTime ( ) ) ;
 }