static void push ( UScriptRun * scriptRun , int32_t pairIndex , UScriptCode scriptCode ) {
 scriptRun -> pushCount = LIMIT_INC ( scriptRun -> pushCount ) ;
 scriptRun -> fixupCount = LIMIT_INC ( scriptRun -> fixupCount ) ;
 scriptRun -> parenSP = INC1 ( scriptRun -> parenSP ) ;
 scriptRun -> parenStack [ scriptRun -> parenSP ] . pairIndex = pairIndex ;
 scriptRun -> parenStack [ scriptRun -> parenSP ] . scriptCode = scriptCode ;
 }