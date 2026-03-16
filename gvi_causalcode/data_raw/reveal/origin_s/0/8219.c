TEST_P ( GLES2DecoderTestWithCHROMIUMPathRendering , IsPathCHROMIUMInvalidArgsBadSharedMemoryId ) {
 EXPECT_CALL ( * gl_ , IsPathNV ( kServicePathId ) ) . Times ( 0 ) ;
 SpecializedSetup < cmds : : IsPathCHROMIUM , 0 > ( false ) ;
 cmds : : IsPathCHROMIUM cmd ;
 cmd . Init ( client_path_id_ , kInvalidSharedMemoryId , shared_memory_offset_ ) ;
 EXPECT_EQ ( error : : kOutOfBounds , ExecuteCmd ( cmd ) ) ;
 cmd . Init ( client_path_id_ , shared_memory_id_ , kInvalidSharedMemoryOffset ) ;
 EXPECT_EQ ( error : : kOutOfBounds , ExecuteCmd ( cmd ) ) ;
 }