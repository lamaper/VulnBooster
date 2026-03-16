TEST_P ( GLES2DecoderTestWithCHROMIUMPathRendering , MatrixLoadIdentityCHROMIUMValidArgs ) {
 EXPECT_CALL ( * gl_ , MatrixLoadIdentityEXT ( GL_PATH_PROJECTION_CHROMIUM ) ) ;
 SpecializedSetup < cmds : : MatrixLoadIdentityCHROMIUM , 0 > ( true ) ;
 cmds : : MatrixLoadIdentityCHROMIUM cmd ;
 cmd . Init ( GL_PATH_PROJECTION_CHROMIUM ) ;
 EXPECT_EQ ( error : : kNoError , ExecuteCmd ( cmd ) ) ;
 EXPECT_EQ ( GL_NO_ERROR , GetGLError ( ) ) ;
 }