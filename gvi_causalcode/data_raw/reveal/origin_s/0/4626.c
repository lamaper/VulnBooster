TEST_P ( GLES2DecoderTestWithCHROMIUMFramebufferMixedSamples , CoverageModulationCHROMIUMValidArgs ) {
 EXPECT_CALL ( * gl_ , CoverageModulationNV ( GL_RGB ) ) ;
 SpecializedSetup < cmds : : CoverageModulationCHROMIUM , 0 > ( true ) ;
 cmds : : CoverageModulationCHROMIUM cmd ;
 cmd . Init ( GL_RGB ) ;
 EXPECT_EQ ( error : : kNoError , ExecuteCmd ( cmd ) ) ;
 EXPECT_EQ ( GL_NO_ERROR , GetGLError ( ) ) ;
 }