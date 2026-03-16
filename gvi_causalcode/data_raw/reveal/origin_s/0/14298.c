void exsltMathRegister ( void ) {
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "min" , EXSLT_MATH_NAMESPACE , exsltMathMinFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "max" , EXSLT_MATH_NAMESPACE , exsltMathMaxFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "highest" , EXSLT_MATH_NAMESPACE , exsltMathHighestFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "lowest" , EXSLT_MATH_NAMESPACE , exsltMathLowestFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "constant" , EXSLT_MATH_NAMESPACE , exsltMathConstantFunction ) ;


 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "sqrt" , EXSLT_MATH_NAMESPACE , exsltMathSqrtFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "power" , EXSLT_MATH_NAMESPACE , exsltMathPowerFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "log" , EXSLT_MATH_NAMESPACE , exsltMathLogFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "sin" , EXSLT_MATH_NAMESPACE , exsltMathSinFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "cos" , EXSLT_MATH_NAMESPACE , exsltMathCosFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "tan" , EXSLT_MATH_NAMESPACE , exsltMathTanFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "asin" , EXSLT_MATH_NAMESPACE , exsltMathAsinFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "acos" , EXSLT_MATH_NAMESPACE , exsltMathAcosFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "atan" , EXSLT_MATH_NAMESPACE , exsltMathAtanFunction ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "atan2" , EXSLT_MATH_NAMESPACE , exsltMathAtan2Function ) ;
 xsltRegisterExtModuleFunction ( ( const xmlChar * ) "exp" , EXSLT_MATH_NAMESPACE , exsltMathExpFunction ) ;
