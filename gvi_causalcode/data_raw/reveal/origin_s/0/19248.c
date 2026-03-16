TEST_P ( GLES2DecoderTestWithBlendEquationAdvanced , BlendBarrierKHRValidArgs ) {
 EXPECT_CALL ( * gl_ , BlendBarrierKHR ( ) ) ;
 SpecializedSetup < cmds : : BlendBarrierKHR , 0 > ( true ) ;
 cmds : : BlendBarrierKHR cmd ;
 cmd . Init ( ) ;
 EXPECT_EQ ( error : : kNoError , ExecuteCmd ( cmd ) ) ;
 EXPECT_EQ ( GL_NO_ERROR , GetGLError ( ) ) ;
 }