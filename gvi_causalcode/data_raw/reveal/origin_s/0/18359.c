static void fixup ( UScriptRun * scriptRun , UScriptCode scriptCode ) {
 int32_t fixupSP = DEC ( scriptRun -> parenSP , scriptRun -> fixupCount ) ;
 while ( scriptRun -> fixupCount -- > 0 ) {
 fixupSP = INC1 ( fixupSP ) ;
 scriptRun -> parenStack [ fixupSP ] . scriptCode = scriptCode ;
 }
 }