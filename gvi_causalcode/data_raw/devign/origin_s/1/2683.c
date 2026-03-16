static inline void RENAME(yuv2packed2)(SwsContext *c, uint16_t *buf0, uint16_t *buf1, uint16_t *uvbuf0, uint16_t *uvbuf1,

                          uint8_t *dest, int dstW, int yalpha, int uvalpha, int y)

{

    int yalpha1=yalpha^4095;

    int uvalpha1=uvalpha^4095;

    int i;


    if (flags&SWS_FULL_CHR_H_INT)

    {

        switch(dstFormat)

        {


        case PIX_FMT_RGB32:

            asm volatile(





FULL_YSCALEYUV2RGB

            "punpcklbw %%mm1, %%mm3    \n\t"  

            "punpcklbw %%mm7, %%mm0    \n\t"  



            "movq      %%mm3, %%mm1    \n\t"

            "punpcklwd %%mm0, %%mm3    \n\t"  

            "punpckhwd %%mm0, %%mm1    \n\t"  



            MOVNTQ(%%mm3,  (%4, %%REGa, 4))

            MOVNTQ(%%mm1, 8(%4, %%REGa, 4))



            "add $4, %%"REG_a"  \n\t"

            "cmp %5, %%"REG_a"  \n\t"

            " jb 1b             \n\t"



            :: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" ((long)dstW),

            "m" (yalpha1), "m" (uvalpha1)

            : "%"REG_a

            );

            break;

        case PIX_FMT_BGR24:

            asm volatile(



FULL_YSCALEYUV2RGB



                                               

            "punpcklbw %%mm1, %%mm3     \n\t"  

            "punpcklbw %%mm7, %%mm0     \n\t"  



            "movq      %%mm3, %%mm1     \n\t"

            "punpcklwd %%mm0, %%mm3     \n\t"  

            "punpckhwd %%mm0, %%mm1     \n\t"  



            "movq      %%mm3, %%mm2     \n\t"  

            "psrlq        $8, %%mm3     \n\t"  

            "pand "MANGLE(bm00000111)", %%mm2   \n\t"  

            "pand "MANGLE(bm11111000)", %%mm3   \n\t"  

            "por       %%mm2, %%mm3     \n\t"  

            "movq      %%mm1, %%mm2     \n\t"

            "psllq       $48, %%mm1     \n\t"  

            "por       %%mm1, %%mm3     \n\t"  



            "movq      %%mm2, %%mm1     \n\t"  

            "psrld       $16, %%mm2     \n\t"  

            "psrlq       $24, %%mm1     \n\t"  

            "por       %%mm2, %%mm1     \n\t"  



            "mov          %4, %%"REG_b" \n\t"

            "add   %%"REG_a", %%"REG_b" \n\t"


             

            "movntq %%mm3,  (%%"REG_b", %%"REG_a", 2)   \n\t"

            "movntq %%mm1, 8(%%"REG_b", %%"REG_a", 2)   \n\t"


            "movd %%mm3,  (%%"REG_b", %%"REG_a", 2)     \n\t"

            "psrlq  $32, %%mm3                          \n\t"

            "movd %%mm3, 4(%%"REG_b", %%"REG_a", 2)     \n\t"

            "movd %%mm1, 8(%%"REG_b", %%"REG_a", 2)     \n\t"


            "add     $4, %%"REG_a"                      \n\t"

            "cmp     %5, %%"REG_a"                      \n\t"

            " jb     1b                                 \n\t"



            :: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "m" (dest), "m" (dstW),

            "m" (yalpha1), "m" (uvalpha1)

            : "%"REG_a, "%"REG_b

            );

            break;

        case PIX_FMT_BGR555:

            asm volatile(



FULL_YSCALEYUV2RGB


            "paddusb "MANGLE(g5Dither)", %%mm1  \n\t"

            "paddusb "MANGLE(r5Dither)", %%mm0  \n\t"

            "paddusb "MANGLE(b5Dither)", %%mm3  \n\t"


            "punpcklbw            %%mm7, %%mm1  \n\t"  

            "punpcklbw            %%mm7, %%mm3  \n\t"  

            "punpcklbw            %%mm7, %%mm0  \n\t"  



            "psrlw                   $3, %%mm3  \n\t"

            "psllw                   $2, %%mm1  \n\t"

            "psllw                   $7, %%mm0  \n\t"

            "pand     "MANGLE(g15Mask)", %%mm1  \n\t"

            "pand     "MANGLE(r15Mask)", %%mm0  \n\t"



            "por                  %%mm3, %%mm1  \n\t"

            "por                  %%mm1, %%mm0  \n\t"



            MOVNTQ(%%mm0, (%4, %%REGa, 2))



            "add $4, %%"REG_a"  \n\t"

            "cmp %5, %%"REG_a"  \n\t"

            " jb 1b             \n\t"



            :: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

            "m" (yalpha1), "m" (uvalpha1)

            : "%"REG_a

            );

            break;

        case PIX_FMT_BGR565:

            asm volatile(



FULL_YSCALEYUV2RGB


            "paddusb "MANGLE(g6Dither)", %%mm1  \n\t"

            "paddusb "MANGLE(r5Dither)", %%mm0  \n\t"

            "paddusb "MANGLE(b5Dither)", %%mm3  \n\t"


            "punpcklbw            %%mm7, %%mm1  \n\t"  

            "punpcklbw            %%mm7, %%mm3  \n\t"  

            "punpcklbw            %%mm7, %%mm0  \n\t"  



            "psrlw                   $3, %%mm3  \n\t"

            "psllw                   $3, %%mm1  \n\t"

            "psllw                   $8, %%mm0  \n\t"

            "pand     "MANGLE(g16Mask)", %%mm1  \n\t"

            "pand     "MANGLE(r16Mask)", %%mm0  \n\t"



            "por                  %%mm3, %%mm1  \n\t"

            "por                  %%mm1, %%mm0  \n\t"



            MOVNTQ(%%mm0, (%4, %%REGa, 2))



            "add $4, %%"REG_a"  \n\t"

            "cmp %5, %%"REG_a"  \n\t"

            " jb 1b             \n\t"



            :: "r" (buf0), "r" (buf1), "r" (uvbuf0), "r" (uvbuf1), "r" (dest), "m" (dstW),

            "m" (yalpha1), "m" (uvalpha1)

            : "%"REG_a

            );

            break;


        case PIX_FMT_BGR32:


        case PIX_FMT_RGB32:


            if (dstFormat==PIX_FMT_RGB32)

            {

                int i;


                dest++;


                for (i=0;i<dstW;i++){

                     

                    int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

                    int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

                    int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);

                    dest[0]=clip_table[((Y + yuvtab_40cf[U]) >>13)];

                    dest[1]=clip_table[((Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13)];

                    dest[2]=clip_table[((Y + yuvtab_3343[V]) >>13)];

                    dest+= 4;

                }

            }

            else if (dstFormat==PIX_FMT_BGR24)

            {

                int i;

                for (i=0;i<dstW;i++){

                     

                    int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

                    int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

                    int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);

                    dest[0]=clip_table[((Y + yuvtab_40cf[U]) >>13)];

                    dest[1]=clip_table[((Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13)];

                    dest[2]=clip_table[((Y + yuvtab_3343[V]) >>13)];

                    dest+= 3;

                }

            }

            else if (dstFormat==PIX_FMT_BGR565)

            {

                int i;

                for (i=0;i<dstW;i++){

                     

                    int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

                    int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

                    int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);



                    ((uint16_t*)dest)[i] =

                        clip_table16b[(Y + yuvtab_40cf[U]) >>13] |

                        clip_table16g[(Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13] |

                        clip_table16r[(Y + yuvtab_3343[V]) >>13];

                }

            }

            else if (dstFormat==PIX_FMT_BGR555)

            {

                int i;

                for (i=0;i<dstW;i++){

                     

                    int Y=yuvtab_2568[((buf0[i]*yalpha1+buf1[i]*yalpha)>>19)];

                    int U=((uvbuf0[i]*uvalpha1+uvbuf1[i]*uvalpha)>>19);

                    int V=((uvbuf0[i+2048]*uvalpha1+uvbuf1[i+2048]*uvalpha)>>19);



                    ((uint16_t*)dest)[i] =

                        clip_table15b[(Y + yuvtab_40cf[U]) >>13] |

                        clip_table15g[(Y + yuvtab_1a1e[V] + yuvtab_0c92[U]) >>13] |

                        clip_table15r[(Y + yuvtab_3343[V]) >>13];

                }

            }

        } 

    else

    {



        switch(c->dstFormat)

        {

             

            case PIX_FMT_RGB32:

                asm volatile(

                "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"

                "mov        %4, %%"REG_b"               \n\t"

                "push %%"REG_BP"                        \n\t"

                YSCALEYUV2RGB(%%REGBP, %5)

                WRITEBGR32(%%REGb, 8280(%5), %%REGBP)

                "pop %%"REG_BP"                         \n\t"

                "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"



                :: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

                "a" (&c->redDither)

                );

                return;

            case PIX_FMT_BGR24:

                asm volatile(

                "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"

                "mov        %4, %%"REG_b"               \n\t"

                "push %%"REG_BP"                        \n\t"

                YSCALEYUV2RGB(%%REGBP, %5)

                WRITEBGR24(%%REGb, 8280(%5), %%REGBP)

                "pop %%"REG_BP"                         \n\t"

                "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"

                :: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

                "a" (&c->redDither)

                );

                return;

            case PIX_FMT_BGR555:

                asm volatile(

                "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"

                "mov        %4, %%"REG_b"               \n\t"

                "push %%"REG_BP"                        \n\t"

                YSCALEYUV2RGB(%%REGBP, %5)


                "paddusb "MANGLE(b5Dither)", %%mm2      \n\t"

                "paddusb "MANGLE(g5Dither)", %%mm4      \n\t"

                "paddusb "MANGLE(r5Dither)", %%mm5      \n\t"




                WRITEBGR15(%%REGb, 8280(%5), %%REGBP)

                "pop %%"REG_BP"                         \n\t"

                "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"



                :: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

                "a" (&c->redDither)

                );

                return;

            case PIX_FMT_BGR565:

                asm volatile(

                "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"

                "mov        %4, %%"REG_b"               \n\t"

                "push %%"REG_BP"                        \n\t"

                YSCALEYUV2RGB(%%REGBP, %5)


                "paddusb "MANGLE(b5Dither)", %%mm2      \n\t"

                "paddusb "MANGLE(g6Dither)", %%mm4      \n\t"

                "paddusb "MANGLE(r5Dither)", %%mm5      \n\t"




                WRITEBGR16(%%REGb, 8280(%5), %%REGBP)

                "pop %%"REG_BP"                         \n\t"

                "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"

                :: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

                "a" (&c->redDither)

                );

                return;

            case PIX_FMT_YUYV422:

                asm volatile(

                "mov %%"REG_b", "ESP_OFFSET"(%5)        \n\t"

                "mov %4, %%"REG_b"                        \n\t"

                "push %%"REG_BP"                        \n\t"

                YSCALEYUV2PACKED(%%REGBP, %5)

                WRITEYUY2(%%REGb, 8280(%5), %%REGBP)

                "pop %%"REG_BP"                         \n\t"

                "mov "ESP_OFFSET"(%5), %%"REG_b"        \n\t"

                :: "c" (buf0), "d" (buf1), "S" (uvbuf0), "D" (uvbuf1), "m" (dest),

                "a" (&c->redDither)

                );

                return;

            default: break;

        }


YSCALE_YUV_2_ANYRGB_C(YSCALE_YUV_2_RGB2_C, YSCALE_YUV_2_PACKED2_C)

}
