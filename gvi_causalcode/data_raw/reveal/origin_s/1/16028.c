TEST_P ( GLES2DecoderTestWithCHROMIUMPathRendering , MatrixLoadfCHROMIUMImmediateValidArgs ) {
 cmds : : MatrixLoadfCHROMIUMImmediate & cmd = * GetImmediateAs < cmds : : MatrixLoadfCHROMIUMImmediate > ( ) ;
 SpecializedSetup < cmds : : MatrixLoadfCHROMIUMImmediate , 0 > ( true ) ;
 GLfloat temp [ 16 ] = {
 0 , }
 ;
 cmd . Init ( GL_PATH_PROJECTION_CHROMIUM , & temp [ 0 ] ) ;
 EXPECT_CALL ( * gl_ , MatrixLoadfEXT ( GL_PATH_PROJECTION_CHROMIUM , reinterpret_cast < GLfloat * > ( ImmediateDataAddress ( & cmd ) ) ) ) ;
 EXPECT_EQ ( error : : kNoError , ExecuteImmediateCmd ( cmd , sizeof ( temp ) ) ) ;
 EXPECT_EQ ( GL_NO_ERROR , GetGLError ( ) ) ;
 }