TEST_F ( BrowsingDataRemoverImplTest , RemoveQuotaManagedIgnoreExtensionsAndDevTools ) {


 EXPECT_EQ ( BrowsingDataRemover : : REMOVE_APPCACHE | BrowsingDataRemover : : REMOVE_SERVICE_WORKERS | BrowsingDataRemover : : REMOVE_CACHE_STORAGE | BrowsingDataRemover : : REMOVE_FILE_SYSTEMS | BrowsingDataRemover : : REMOVE_INDEXEDDB | BrowsingDataRemover : : REMOVE_WEBSQL , GetRemovalMask ( ) ) ;
 EXPECT_EQ ( BrowsingDataHelper : : UNPROTECTED_WEB , GetOriginTypeMask ( ) ) ;
 StoragePartitionRemovalData removal_data = GetStoragePartitionRemovalData ( ) ;
 EXPECT_EQ ( removal_data . remove_mask , StoragePartition : : REMOVE_DATA_MASK_FILE_SYSTEMS | StoragePartition : : REMOVE_DATA_MASK_WEBSQL | StoragePartition : : REMOVE_DATA_MASK_APPCACHE | StoragePartition : : REMOVE_DATA_MASK_SERVICE_WORKERS | StoragePartition : : REMOVE_DATA_MASK_CACHE_STORAGE | StoragePartition : : REMOVE_DATA_MASK_INDEXEDDB ) ;
 EXPECT_EQ ( removal_data . quota_storage_remove_mask , StoragePartition : : QUOTA_MANAGED_STORAGE_MASK_ALL ) ;
 EXPECT_FALSE ( removal_data . origin_matcher . Run ( kOriginExt , mock_policy ( ) ) ) ;
 EXPECT_FALSE ( removal_data . origin_matcher . Run ( kOriginDevTools , mock_policy ( ) ) ) ;
 }