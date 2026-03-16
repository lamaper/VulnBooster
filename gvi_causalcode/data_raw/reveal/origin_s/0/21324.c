TEST_P ( GLES2DecoderTestWithCHROMIUMPathRendering , PathStencilFuncCHROMIUMValidArgs ) {
 EXPECT_CALL ( * gl_ , PathStencilFuncNV ( GL_NEVER , 2 , 3 ) ) ;
 SpecializedSetup < cmds : : PathStencilFuncCHROMIUM , 0 > ( true ) ;
 cmds : : PathStencilFuncCHROMIUM cmd ;
 cmd . Init ( GL_NEVER , 2 , 3 ) ;
 EXPECT_EQ ( error : : kNoError , ExecuteCmd ( cmd ) ) ;
 EXPECT_EQ ( GL_NO_ERROR , GetGLError ( ) ) ;
 }