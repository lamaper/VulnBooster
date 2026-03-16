static void pop ( UScriptRun * scriptRun ) {
 if ( STACK_IS_EMPTY ( scriptRun ) ) {
 return ;
 }
 if ( scriptRun -> fixupCount > 0 ) {
 scriptRun -> fixupCount -= 1 ;
 }
 scriptRun -> pushCount -= 1 ;
 scriptRun -> parenSP = DEC1 ( scriptRun -> parenSP ) ;
 if ( STACK_IS_EMPTY ( scriptRun ) ) {
 scriptRun -> parenSP = - 1 ;
 }
 }