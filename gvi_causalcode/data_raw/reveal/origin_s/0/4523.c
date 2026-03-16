TEST_P ( GLES2DecoderTestWithCHROMIUMPathRendering , IsPathCHROMIUMValidArgs ) {
 EXPECT_CALL ( * gl_ , IsPathNV ( kServicePathId ) ) ;
 SpecializedSetup < cmds : : IsPathCHROMIUM , 0 > ( true ) ;
 cmds : : IsPathCHROMIUM cmd ;
 cmd . Init ( client_path_id_ , shared_memory_id_ , shared_memory_offset_ ) ;
 EXPECT_EQ ( error : : kNoError , ExecuteCmd ( cmd ) ) ;
 EXPECT_EQ ( GL_NO_ERROR , GetGLError ( ) ) ;
 }