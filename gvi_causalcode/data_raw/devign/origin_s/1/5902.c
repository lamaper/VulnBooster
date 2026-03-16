static void utf8_string(void)

{

     

    static const struct {

        const char *json_in;

        const char *utf8_out;

        const char *json_out;    

        const char *utf8_in;     

    } test_cases[] = {

         



         

        {

             

            "\"Falsches \xC3\x9C" "ben von Xylophonmusik qu\xC3\xA4lt"

            " jeden gr\xC3\xB6\xC3\x9F" "eren Zwerg.\"",

            "Falsches \xC3\x9C" "ben von Xylophonmusik qu\xC3\xA4lt"

            " jeden gr\xC3\xB6\xC3\x9F" "eren Zwerg.",

            "\"Falsches \\u00DCben von Xylophonmusik qu\\u00E4lt"

            " jeden gr\\u00F6\\u00DFeren Zwerg.\"",

        },

        {

             

            "\"\xCE\xBA\xE1\xBD\xB9\xCF\x83\xCE\xBC\xCE\xB5\"",

            "\xCE\xBA\xE1\xBD\xB9\xCF\x83\xCE\xBC\xCE\xB5",

            "\"\\u03BA\\u1F79\\u03C3\\u03BC\\u03B5\"",

        },

         

         

         

        {

            "\"\\u0000\"",

            "",                  

            "\"\\u0000\"",

            "\xC0\x80",

        },

         

        {

            "\"\xC2\x80\"",

            "\xC2\x80",

            "\"\\u0080\"",

        },

         

        {

            "\"\xE0\xA0\x80\"",

            "\xE0\xA0\x80",

            "\"\\u0800\"",

        },

         

        {

            "\"\xF0\x90\x80\x80\"",

            "\xF0\x90\x80\x80",

            "\"\\uD800\\uDC00\"",

        },

         

        {

            "\"\xF8\x88\x80\x80\x80\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xF8\x88\x80\x80\x80",

        },

         

        {

            "\"\xFC\x84\x80\x80\x80\x80\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xFC\x84\x80\x80\x80\x80",

        },

         

         

        {

            "\"\x7F\"",

            "\x7F",

            "\"\\u007F\"",

        },

         

        {

            "\"\xDF\xBF\"",

            "\xDF\xBF",

            "\"\\u07FF\"",

        },

         

        {

            "\"\xEF\xBF\xBC\"",

            "\xEF\xBF\xBC",

            "\"\\uFFFC\"",

        },

         

        {

            "\"\xF7\xBF\xBF\xBF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xF7\xBF\xBF\xBF",

        },

         

        {

            "\"\xFB\xBF\xBF\xBF\xBF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xFB\xBF\xBF\xBF\xBF",

        },

         

        {

            "\"\xFD\xBF\xBF\xBF\xBF\xBF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xFD\xBF\xBF\xBF\xBF\xBF",

        },

         

        {

             

            "\"\xED\x9F\xBF\"",

            "\xED\x9F\xBF",

            "\"\\uD7FF\"",

        },

        {

             

            "\"\xEE\x80\x80\"",

            "\xEE\x80\x80",

            "\"\\uE000\"",

        },

        {

             

            "\"\xEF\xBF\xBD\"",

            "\xEF\xBF\xBD",

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xF4\x8F\xBF\xBD\"",

            "\xF4\x8F\xBF\xBD",

            "\"\\uDBFF\\uDFFD\""

        },

        {

             

            "\"\xF4\x90\x80\x80\"",

            "\xF4\x90\x80\x80",

            "\"\\uFFFD\"",

        },

         

         

         

        {

            "\"\x80\"",

            "\x80",              

            "\"\\uFFFD\"",

        },

         

        {

            "\"\xBF\"",

            "\xBF",              

            "\"\\uFFFD\"",

        },

         

        {

            "\"\x80\xBF\"",

            "\x80\xBF",          

            "\"\\uFFFD\\uFFFD\"",

        },

         

        {

            "\"\x80\xBF\x80\"",

            "\x80\xBF\x80",      

            "\"\\uFFFD\\uFFFD\\uFFFD\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\"",

            "\x80\xBF\x80\xBF",  

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\x80\"",

            "\x80\xBF\x80\xBF\x80",  

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\x80\xBF\"",

            "\x80\xBF\x80\xBF\x80\xBF",  

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\x80\xBF\x80\"",

            "\x80\xBF\x80\xBF\x80\xBF\x80",  

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

        },

         

        {

            "\"\x80\x81\x82\x83\x84\x85\x86\x87"

            "\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"

            "\x90\x91\x92\x93\x94\x95\x96\x97"

            "\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"

            "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7"

            "\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"

            "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7"

            "\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF\"",

              

            "\x80\x81\x82\x83\x84\x85\x86\x87"

            "\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"

            "\x90\x91\x92\x93\x94\x95\x96\x97"

            "\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"

            "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7"

            "\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"

            "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7"

            "\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF",

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\""

        },

         

         

        {

            "\"\xC0 \xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 "

            "\xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF "

            "\xD0 \xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 "

            "\xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF \"",

            NULL,                

            "\"\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD "

            "\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD "

            "\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD "

            "\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \"",

            "\xC0 \xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 "

            "\xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF "

            "\xD0 \xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 "

            "\xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF ",

        },

         

        {

            "\"\xE0 \xE1 \xE2 \xE3 \xE4 \xE5 \xE6 \xE7 "

            "\xE8 \xE9 \xEA \xEB \xEC \xED \xEE \xEF \"",

             

            "\xE0 \xE1 \xE2 \xE3 \xE4 \xE5 \xE6 \xE7 "

            "\xE8 \xE9 \xEA \xEB \xEC \xED \xEE \xEF ",

            "\"\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD "

            "\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \"",

        },

         

        {

            "\"\xF0 \xF1 \xF2 \xF3 \xF4 \xF5 \xF6 \xF7 \"",

            NULL,                

            "\"\\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \\uFFFD \"",

            "\xF0 \xF1 \xF2 \xF3 \xF4 \xF5 \xF6 \xF7 ",

        },

         

        {

            "\"\xF8 \xF9 \xFA \xFB \"",

            NULL,                

            "\"\\uFFFD \\uFFFD \\uFFFD \\uFFFD \"",

            "\xF8 \xF9 \xFA \xFB ",

        },

         

        {

            "\"\xFC \xFD \"",

            NULL,                

            "\"\\uFFFD \\uFFFD \"",

            "\xFC \xFD ",

        },

         

         

        {

            "\"\xC0\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xC0",

        },

         

        {

            "\"\xE0\x80\"",

            "\xE0\x80",            

            "\"\\uFFFD\"",

        },

         

        {

            "\"\xF0\x80\x80\"",

            "\xF0\x80\x80",      

            "\"\\uFFFD\"",

        },

         

        {

            "\"\xF8\x80\x80\x80\"",

            NULL,                    

            "\"\\uFFFD\"",

            "\xF8\x80\x80\x80",

        },

         

        {

            "\"\xFC\x80\x80\x80\x80\"",

            NULL,                         

            "\"\\uFFFD\"",

            "\xFC\x80\x80\x80\x80",

        },

         

        {

            "\"\xDF\"",

            "\xDF",              

            "\"\\uFFFD\"",

        },

         

        {

            "\"\xEF\xBF\"",

            "\xEF\xBF",            

            "\"\\uFFFD\"",

        },

         

        {

            "\"\xF7\xBF\xBF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xF7\xBF\xBF",

        },

         

        {

            "\"\xFB\xBF\xBF\xBF\"",

            NULL,                  

            "\"\\uFFFD\"",

            "\xFB\xBF\xBF\xBF",

        },

         

        {

            "\"\xFD\xBF\xBF\xBF\xBF\"",

            NULL,                         

            "\"\\uFFFD\"",

            "\xFD\xBF\xBF\xBF\xBF",

        },

         

        {

            "\"\xC0\xE0\x80\xF0\x80\x80\xF8\x80\x80\x80\xFC\x80\x80\x80\x80"

            "\xDF\xEF\xBF\xF7\xBF\xBF\xFB\xBF\xBF\xBF\xFD\xBF\xBF\xBF\xBF\"",

            NULL,                

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

            "\xC0\xE0\x80\xF0\x80\x80\xF8\x80\x80\x80\xFC\x80\x80\x80\x80"

            "\xDF\xEF\xBF\xF7\xBF\xBF\xFB\xBF\xBF\xBF\xFD\xBF\xBF\xBF\xBF",

        },

         

        {

            "\"\xFE\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xFE",

        },

        {

            "\"\xFF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xFF",

        },

        {

            "\"\xFE\xFE\xFF\xFF\"",

            NULL,                  

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

            "\xFE\xFE\xFF\xFF",

        },

         

         

        {

            "\"\xC0\xAF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xC0\xAF",

        },

        {

            "\"\xE0\x80\xAF\"",

            "\xE0\x80\xAF",      

            "\"\\uFFFD\"",

        },

        {

            "\"\xF0\x80\x80\xAF\"",

            "\xF0\x80\x80\xAF",   

            "\"\\uFFFD\"",

        },

        {

            "\"\xF8\x80\x80\x80\xAF\"",

            NULL,                         

            "\"\\uFFFD\"",

            "\xF8\x80\x80\x80\xAF",

        },

        {

            "\"\xFC\x80\x80\x80\x80\xAF\"",

            NULL,                                

            "\"\\uFFFD\"",

            "\xFC\x80\x80\x80\x80\xAF",

        },

         

        {

             

            "\"\xC1\xBF\"",

            NULL,                

            "\"\\uFFFD\"",

            "\xC1\xBF",

        },

        {

             

            "\"\xE0\x9F\xBF\"",

            "\xE0\x9F\xBF",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xF0\x8F\xBF\xBC\"",

            "\xF0\x8F\xBF\xBC",    

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xF8\x87\xBF\xBF\xBF\"",

            NULL,                         

            "\"\\uFFFD\"",

            "\xF8\x87\xBF\xBF\xBF",

        },

        {

             

            "\"\xFC\x83\xBF\xBF\xBF\xBF\"",

            NULL,                                

            "\"\\uFFFD\"",

            "\xFC\x83\xBF\xBF\xBF\xBF",

        },

         

        {

             

            "\"\xC0\x80\"",

            NULL,                

            "\"\\u0000\"",

            "\xC0\x80",

        },

        {

             

            "\"\xE0\x80\x80\"",

            "\xE0\x80\x80",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xF0\x80\x80\x80\"",

            "\xF0\x80\x80\x80",    

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xF8\x80\x80\x80\x80\"",

            NULL,                         

            "\"\\uFFFD\"",

            "\xF8\x80\x80\x80\x80",

        },

        {

             

            "\"\xFC\x80\x80\x80\x80\x80\"",

            NULL,                                

            "\"\\uFFFD\"",

            "\xFC\x80\x80\x80\x80\x80",

        },

         

         

        {

             

            "\"\xED\xA0\x80\"",

            "\xED\xA0\x80",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xED\xAD\xBF\"",

            "\xED\xAD\xBF",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xED\xAE\x80\"",

            "\xED\xAE\x80",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xED\xAF\xBF\"",

            "\xED\xAF\xBF",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xED\xB0\x80\"",

            "\xED\xB0\x80",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xED\xBE\x80\"",

            "\xED\xBE\x80",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xED\xBF\xBF\"",

            "\xED\xBF\xBF",      

            "\"\\uFFFD\"",

        },

         

        {

             

            "\"\xED\xA0\x80\xED\xB0\x80\"",

            "\xED\xA0\x80\xED\xB0\x80",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xA0\x80\xED\xBF\xBF\"",

            "\xED\xA0\x80\xED\xBF\xBF",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xAD\xBF\xED\xB0\x80\"",

            "\xED\xAD\xBF\xED\xB0\x80",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xAD\xBF\xED\xBF\xBF\"",

            "\xED\xAD\xBF\xED\xBF\xBF",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xAE\x80\xED\xB0\x80\"",

            "\xED\xAE\x80\xED\xB0\x80",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xAE\x80\xED\xBF\xBF\"",

            "\xED\xAE\x80\xED\xBF\xBF",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xAF\xBF\xED\xB0\x80\"",

            "\xED\xAF\xBF\xED\xB0\x80",  

            "\"\\uFFFD\\uFFFD\"",

        },

        {

             

            "\"\xED\xAF\xBF\xED\xBF\xBF\"",

            "\xED\xAF\xBF\xED\xBF\xBF",  

            "\"\\uFFFD\\uFFFD\"",

        },

         

         

        {

             

            "\"\xEF\xBF\xBE\"",

            "\xEF\xBF\xBE",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xEF\xBF\xBF\"",

            "\xEF\xBF\xBF",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xEF\xB7\x90\"",

            "\xEF\xB7\x90",      

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xEF\xB7\xAF\"",

            "\xEF\xB7\xAF",      

            "\"\\uFFFD\"",

        },

         

        {

             

            "\"\xF0\x9F\xBF\xBE\xF0\x9F\xBF\xBF"

            "\xF0\xAF\xBF\xBE\xF0\xAF\xBF\xBF"

            "\xF0\xBF\xBF\xBE\xF0\xBF\xBF\xBF"

            "\xF1\x8F\xBF\xBE\xF1\x8F\xBF\xBF"

            "\xF1\x9F\xBF\xBE\xF1\x9F\xBF\xBF"

            "\xF1\xAF\xBF\xBE\xF1\xAF\xBF\xBF"

            "\xF1\xBF\xBF\xBE\xF1\xBF\xBF\xBF"

            "\xF2\x8F\xBF\xBE\xF2\x8F\xBF\xBF"

            "\xF2\x9F\xBF\xBE\xF2\x9F\xBF\xBF"

            "\xF2\xAF\xBF\xBE\xF2\xAF\xBF\xBF"

            "\xF2\xBF\xBF\xBE\xF2\xBF\xBF\xBF"

            "\xF3\x8F\xBF\xBE\xF3\x8F\xBF\xBF"

            "\xF3\x9F\xBF\xBE\xF3\x9F\xBF\xBF"

            "\xF3\xAF\xBF\xBE\xF3\xAF\xBF\xBF"

            "\xF3\xBF\xBF\xBE\xF3\xBF\xBF\xBF"

            "\xF4\x8F\xBF\xBE\xF4\x8F\xBF\xBF\"",

             

            "\xF0\x9F\xBF\xBE\xF0\x9F\xBF\xBF"

            "\xF0\xAF\xBF\xBE\xF0\xAF\xBF\xBF"

            "\xF0\xBF\xBF\xBE\xF0\xBF\xBF\xBF"

            "\xF1\x8F\xBF\xBE\xF1\x8F\xBF\xBF"

            "\xF1\x9F\xBF\xBE\xF1\x9F\xBF\xBF"

            "\xF1\xAF\xBF\xBE\xF1\xAF\xBF\xBF"

            "\xF1\xBF\xBF\xBE\xF1\xBF\xBF\xBF"

            "\xF2\x8F\xBF\xBE\xF2\x8F\xBF\xBF"

            "\xF2\x9F\xBF\xBE\xF2\x9F\xBF\xBF"

            "\xF2\xAF\xBF\xBE\xF2\xAF\xBF\xBF"

            "\xF2\xBF\xBF\xBE\xF2\xBF\xBF\xBF"

            "\xF3\x8F\xBF\xBE\xF3\x8F\xBF\xBF"

            "\xF3\x9F\xBF\xBE\xF3\x9F\xBF\xBF"

            "\xF3\xAF\xBF\xBE\xF3\xAF\xBF\xBF"

            "\xF3\xBF\xBF\xBE\xF3\xBF\xBF\xBF"

            "\xF4\x8F\xBF\xBE\xF4\x8F\xBF\xBF",

            "\"\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD"

            "\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\\uFFFD\"",

        },

        {}

    };

    int i;

    QObject *obj;

    QString *str;

    const char *json_in, *utf8_out, *utf8_in, *json_out;



    for (i = 0; test_cases[i].json_in; i++) {

        json_in = test_cases[i].json_in;

        utf8_out = test_cases[i].utf8_out;

        utf8_in = test_cases[i].utf8_in ?: test_cases[i].utf8_out;

        json_out = test_cases[i].json_out ?: test_cases[i].json_in;



        obj = qobject_from_json(json_in, NULL);

        if (utf8_out) {

            str = qobject_to_qstring(obj);

            g_assert(str);

            g_assert_cmpstr(qstring_get_str(str), ==, utf8_out);

        } else {

            g_assert(!obj);

        }

        qobject_decref(obj);



        obj = QOBJECT(qstring_from_str(utf8_in));

        str = qobject_to_json(obj);

        if (json_out) {

            g_assert(str);

            g_assert_cmpstr(qstring_get_str(str), ==, json_out);

        } else {

            g_assert(!str);

        }

        QDECREF(str);

        qobject_decref(obj);



         

        if (0 && json_out != json_in) {

            obj = qobject_from_json(json_out, NULL);

            str = qobject_to_qstring(obj);

            g_assert(str);

            g_assert_cmpstr(qstring_get_str(str), ==, utf8_out);

        }

    }

}
