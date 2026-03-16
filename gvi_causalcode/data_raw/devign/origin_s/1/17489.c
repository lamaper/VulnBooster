print_insn_sparc (bfd_vma memaddr, disassemble_info *info)

{

  FILE *stream = info->stream;

  bfd_byte buffer[4];

  unsigned long insn;

  sparc_opcode_hash *op;

   

  static int opcodes_initialized = 0;

   

  static unsigned long current_mach = 0;

  bfd_vma (*getword) (const unsigned char *);



  if (!opcodes_initialized

      || info->mach != current_mach)

    {

      int i;



      current_arch_mask = compute_arch_mask (info->mach);



      if (!opcodes_initialized)

        sorted_opcodes =

          malloc (sparc_num_opcodes * sizeof (sparc_opcode *));

       

      for (i = 0; i < sparc_num_opcodes; ++i)

        sorted_opcodes[i] = &sparc_opcodes[i];

      qsort ((char *) sorted_opcodes, sparc_num_opcodes,

             sizeof (sorted_opcodes[0]), compare_opcodes);



      build_hash_table (sorted_opcodes, opcode_hash_table, sparc_num_opcodes);

      current_mach = info->mach;

      opcodes_initialized = 1;

    }



  {

    int status =

      (*info->read_memory_func) (memaddr, buffer, sizeof (buffer), info);



    if (status != 0)

      {

        (*info->memory_error_func) (status, memaddr, info);

        return -1;

      }

  }



   

  if (info->endian == BFD_ENDIAN_BIG || info->mach == bfd_mach_sparc_sparclite)

    getword = bfd_getb32;

  else

    getword = bfd_getl32;



  insn = getword (buffer);



  info->insn_info_valid = 1;                     

  info->insn_type = dis_nonbranch;               

  info->branch_delay_insns = 0;                  

  info->target = 0;                              



  for (op = opcode_hash_table[HASH_INSN (insn)]; op; op = op->next)

    {

      const sparc_opcode *opcode = op->opcode;



       

      if (! (opcode->architecture & current_arch_mask))

        continue;



      if ((opcode->match & insn) == opcode->match

          && (opcode->lose & insn) == 0)

        {

           

          int imm_added_to_rs1 = 0;

          int imm_ored_to_rs1 = 0;



           

          int found_plus = 0;



           

             



           

          if (opcode->match == 0x80102000)  

            imm_ored_to_rs1 = 1;

          if (opcode->match == 0x80002000)  

            imm_added_to_rs1 = 1;



          if (X_RS1 (insn) != X_RD (insn)

              && strchr (opcode->args, 'r') != NULL)

               

              continue;

          if (X_RS2 (insn) != X_RD (insn)

              && strchr (opcode->args, 'O') != NULL)

               

              continue;



          (*info->fprintf_func) (stream, "%s", opcode->name);



          {

            const char *s;



            if (opcode->args[0] != ',')

              (*info->fprintf_func) (stream, " ");



            for (s = opcode->args; *s != '\0'; ++s)

              {

                while (*s == ',')

                  {

                    (*info->fprintf_func) (stream, ",");

                    ++s;

                    switch (*s)

                      {

                      case 'a':

                        (*info->fprintf_func) (stream, "a");

                           

                        ++s;

                        continue;

                      case 'N':

                        (*info->fprintf_func) (stream, "pn");

                        ++s;

                        continue;



                      case 'T':

                        (*info->fprintf_func) (stream, "pt");

                        ++s;

                        continue;



                      default:

                        break;

                      }

                  }



                (*info->fprintf_func) (stream, " ");



                switch (*s)

                  {

                  case '+':

                    found_plus = 1;

                     



                  default:

                    (*info->fprintf_func) (stream, "%c", *s);

                    break;



                  case '#':

                    (*info->fprintf_func) (stream, "0");

                    break;


                  case '1':

                  case 'r':

                    reg (X_RS1 (insn));

                    break;



                  case '2':

                  case 'O':

                    reg (X_RS2 (insn));

                    break;



                  case 'd':

                    reg (X_RD (insn));

                    break;




                  case 'e':

                    freg (X_RS1 (insn));

                    break;

                  case 'v':      

                  case 'V':      

                    fregx (X_RS1 (insn));

                    break;



                  case 'f':

                    freg (X_RS2 (insn));

                    break;

                  case 'B':      

                  case 'R':      

                    fregx (X_RS2 (insn));

                    break;



                  case 'g':

                    freg (X_RD (insn));

                    break;

                  case 'H':      

                  case 'J':      

                    fregx (X_RD (insn));

                    break;




                  case 'b':

                    creg (X_RS1 (insn));

                    break;



                  case 'c':

                    creg (X_RS2 (insn));

                    break;



                  case 'D':

                    creg (X_RD (insn));

                    break;




                  case 'h':

                    (*info->fprintf_func) (stream, "%%hi(%#x)",

                                           ((unsigned) 0xFFFFFFFF

                                            & ((int) X_IMM22 (insn) << 10)));

                    break;



                  case 'i':      

                  case 'I':      

                  case 'j':      

                    {

                      int imm;



                      if (*s == 'i')

                        imm = X_SIMM (insn, 13);

                      else if (*s == 'I')

                        imm = X_SIMM (insn, 11);

                      else

                        imm = X_SIMM (insn, 10);



                       

                      if (found_plus)

                        imm_added_to_rs1 = 1;



                      if (imm <= 9)

                        (*info->fprintf_func) (stream, "%d", imm);

                      else

                        (*info->fprintf_func) (stream, "%#x", imm);

                    }

                    break;



                  case 'X':      

                  case 'Y':      

                    {

                      int imm = X_IMM (insn, *s == 'X' ? 5 : 6);



                      if (imm <= 9)

                        (info->fprintf_func) (stream, "%d", imm);

                      else

                        (info->fprintf_func) (stream, "%#x", (unsigned) imm);

                    }

                    break;



                  case '3':

                    (info->fprintf_func) (stream, "%ld", X_IMM (insn, 3));

                    break;



                  case 'K':

                    {

                      int mask = X_MEMBAR (insn);

                      int bit = 0x40, printed_one = 0;

                      const char *name;



                      if (mask == 0)

                        (info->fprintf_func) (stream, "0");

                      else

                        while (bit)

                          {

                            if (mask & bit)

                              {

                                if (printed_one)

                                  (info->fprintf_func) (stream, "|");

                                name = sparc_decode_membar (bit);

                                (info->fprintf_func) (stream, "%s", name);

                                printed_one = 1;

                              }

                            bit >>= 1;

                          }

                      break;

                    }



                  case 'k':

                    info->target = memaddr + SEX (X_DISP16 (insn), 16) * 4;

                    (*info->print_address_func) (info->target, info);

                    break;



                  case 'G':

                    info->target = memaddr + SEX (X_DISP19 (insn), 19) * 4;

                    (*info->print_address_func) (info->target, info);

                    break;



                  case '6':

                  case '7':

                  case '8':

                  case '9':

                    (*info->fprintf_func) (stream, "%%fcc%c", *s - '6' + '0');

                    break;



                  case 'z':

                    (*info->fprintf_func) (stream, "%%icc");

                    break;



                  case 'Z':

                    (*info->fprintf_func) (stream, "%%xcc");

                    break;



                  case 'E':

                    (*info->fprintf_func) (stream, "%%ccr");

                    break;



                  case 's':

                    (*info->fprintf_func) (stream, "%%fprs");

                    break;



                  case 'o':

                    (*info->fprintf_func) (stream, "%%asi");

                    break;



                  case 'W':

                    (*info->fprintf_func) (stream, "%%tick");

                    break;



                  case 'P':

                    (*info->fprintf_func) (stream, "%%pc");

                    break;



                  case '?':

                    if (X_RS1 (insn) == 31)

                      (*info->fprintf_func) (stream, "%%ver");

                    else if ((unsigned) X_RS1 (insn) < 17)

                      (*info->fprintf_func) (stream, "%%%s",

                                             v9_priv_reg_names[X_RS1 (insn)]);

                    else

                      (*info->fprintf_func) (stream, "%%reserved");

                    break;



                  case '!':

                    if ((unsigned) X_RD (insn) < 17)

                      (*info->fprintf_func) (stream, "%%%s",

                                             v9_priv_reg_names[X_RD (insn)]);

                    else

                      (*info->fprintf_func) (stream, "%%reserved");

                    break;



                  case '$':

                    if ((unsigned) X_RS1 (insn) < 32)

                      (*info->fprintf_func) (stream, "%%%s",

                                             v9_hpriv_reg_names[X_RS1 (insn)]);

                    else

                      (*info->fprintf_func) (stream, "%%reserved");

                    break;



                  case '%':

                    if ((unsigned) X_RD (insn) < 32)

                      (*info->fprintf_func) (stream, "%%%s",

                                             v9_hpriv_reg_names[X_RD (insn)]);

                    else

                      (*info->fprintf_func) (stream, "%%reserved");

                    break;



                  case '/':

                    if (X_RS1 (insn) < 16 || X_RS1 (insn) > 25)

                      (*info->fprintf_func) (stream, "%%reserved");

                    else

                      (*info->fprintf_func) (stream, "%%%s",

                                             v9a_asr_reg_names[X_RS1 (insn)-16]);

                    break;



                  case '_':

                    if (X_RD (insn) < 16 || X_RD (insn) > 25)

                      (*info->fprintf_func) (stream, "%%reserved");

                    else

                      (*info->fprintf_func) (stream, "%%%s",

                                             v9a_asr_reg_names[X_RD (insn)-16]);

                    break;



                  case '*':

                    {

                      const char *name = sparc_decode_prefetch (X_RD (insn));



                      if (name)

                        (*info->fprintf_func) (stream, "%s", name);

                      else

                        (*info->fprintf_func) (stream, "%ld", X_RD (insn));

                      break;

                    }



                  case 'M':

                    (*info->fprintf_func) (stream, "%%asr%ld", X_RS1 (insn));

                    break;



                  case 'm':

                    (*info->fprintf_func) (stream, "%%asr%ld", X_RD (insn));

                    break;



                  case 'L':

                    info->target = memaddr + SEX (X_DISP30 (insn), 30) * 4;

                    (*info->print_address_func) (info->target, info);

                    break;



                  case 'n':

                    (*info->fprintf_func)

                      (stream, "%#x", SEX (X_DISP22 (insn), 22));

                    break;



                  case 'l':

                    info->target = memaddr + SEX (X_DISP22 (insn), 22) * 4;

                    (*info->print_address_func) (info->target, info);

                    break;



                  case 'A':

                    {

                      const char *name;



                      if ((info->mach == bfd_mach_sparc_v8plusa) ||

                          ((info->mach >= bfd_mach_sparc_v9) &&

                           (info->mach <= bfd_mach_sparc_v9b)))

                        name = sparc_decode_asi_v9 (X_ASI (insn));

                      else

                        name = sparc_decode_asi_v8 (X_ASI (insn));



                      if (name)

                        (*info->fprintf_func) (stream, "%s", name);

                      else

                        (*info->fprintf_func) (stream, "(%ld)", X_ASI (insn));

                      break;

                    }



                  case 'C':

                    (*info->fprintf_func) (stream, "%%csr");

                    break;



                  case 'F':

                    (*info->fprintf_func) (stream, "%%fsr");

                    break;



                  case 'p':

                    (*info->fprintf_func) (stream, "%%psr");

                    break;



                  case 'q':

                    (*info->fprintf_func) (stream, "%%fq");

                    break;



                  case 'Q':

                    (*info->fprintf_func) (stream, "%%cq");

                    break;



                  case 't':

                    (*info->fprintf_func) (stream, "%%tbr");

                    break;



                  case 'w':

                    (*info->fprintf_func) (stream, "%%wim");

                    break;



                  case 'x':

                    (*info->fprintf_func) (stream, "%ld",

                                           ((X_LDST_I (insn) << 8)

                                            + X_ASI (insn)));

                    break;



                  case 'y':

                    (*info->fprintf_func) (stream, "%%y");

                    break;



                  case 'u':

                  case 'U':

                    {

                      int val = *s == 'U' ? X_RS1 (insn) : X_RD (insn);

                      const char *name = sparc_decode_sparclet_cpreg (val);



                      if (name)

                        (*info->fprintf_func) (stream, "%s", name);

                      else

                        (*info->fprintf_func) (stream, "%%cpreg(%d)", val);

                      break;

                    }

                  }

              }

          }



           

          if (imm_ored_to_rs1 || imm_added_to_rs1)

            {

              unsigned long prev_insn;

              int errcode;



              if (memaddr >= 4)

                errcode =

                  (*info->read_memory_func)

                  (memaddr - 4, buffer, sizeof (buffer), info);

              else

                errcode = 1;



              prev_insn = getword (buffer);



              if (errcode == 0)

                {

                   



                  if (is_delayed_branch (prev_insn))

                    {

                      if (memaddr >= 8)

                        errcode = (*info->read_memory_func)

                          (memaddr - 8, buffer, sizeof (buffer), info);

                      else

                        errcode = 1;



                      prev_insn = getword (buffer);

                    }

                }



               

              if (errcode == 0)

                {

                   

                  if ((prev_insn & 0xc1c00000) == 0x01000000

                      && X_RD (prev_insn) == X_RS1 (insn))

                    {

                      (*info->fprintf_func) (stream, "\t! ");

                      info->target =

                        ((unsigned) 0xFFFFFFFF

                         & ((int) X_IMM22 (prev_insn) << 10));

                      if (imm_added_to_rs1)

                        info->target += X_SIMM (insn, 13);

                      else

                        info->target |= X_SIMM (insn, 13);

                      (*info->print_address_func) (info->target, info);

                      info->insn_type = dis_dref;

                      info->data_size = 4;   

                    }

                }

            }



          if (opcode->flags & (F_UNBR|F_CONDBR|F_JSR))

            {

                 

              if (opcode->flags & F_UNBR)

                info->insn_type = dis_branch;

              if (opcode->flags & F_CONDBR)

                info->insn_type = dis_condbranch;

              if (opcode->flags & F_JSR)

                info->insn_type = dis_jsr;

              if (opcode->flags & F_DELAYED)

                info->branch_delay_insns = 1;

            }



          return sizeof (buffer);

        }

    }



  info->insn_type = dis_noninsn;         

  (*info->fprintf_func) (stream, _("unknown"));

  return sizeof (buffer);

}
