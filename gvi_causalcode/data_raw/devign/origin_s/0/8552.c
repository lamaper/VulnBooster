int load_elf_binary(struct linux_binprm * bprm, struct target_pt_regs * regs,

                    struct image_info * info)

{

    struct elfhdr elf_ex;

    struct elfhdr interp_elf_ex;

    struct exec interp_ex;

    int interpreter_fd = -1;  

    abi_ulong load_addr, load_bias;

    int load_addr_set = 0;

    unsigned int interpreter_type = INTERPRETER_NONE;

    unsigned char ibcs2_interpreter;

    int i;

    abi_ulong mapped_addr;

    struct elf_phdr * elf_ppnt;

    struct elf_phdr *elf_phdata;

    abi_ulong k, elf_brk;

    int retval;

    char * elf_interpreter;

    abi_ulong elf_entry, interp_load_addr = 0;

    int status;

    abi_ulong start_code, end_code, start_data, end_data;

    abi_ulong reloc_func_desc = 0;

    abi_ulong elf_stack;

    char passed_fileno[6];



    ibcs2_interpreter = 0;

    status = 0;

    load_addr = 0;

    load_bias = 0;

    elf_ex = *((struct elfhdr *) bprm->buf);           

    bswap_ehdr(&elf_ex);



     

    if ((elf_ex.e_type != ET_EXEC && elf_ex.e_type != ET_DYN) ||

        (! elf_check_arch(elf_ex.e_machine))) {

        return -ENOEXEC;

    }



    bprm->p = copy_elf_strings(1, &bprm->filename, bprm->page, bprm->p);

    bprm->p = copy_elf_strings(bprm->envc,bprm->envp,bprm->page,bprm->p);

    bprm->p = copy_elf_strings(bprm->argc,bprm->argv,bprm->page,bprm->p);

    if (!bprm->p) {

        retval = -E2BIG;

    }



     

    elf_phdata = (struct elf_phdr *)malloc(elf_ex.e_phentsize*elf_ex.e_phnum);

    if (elf_phdata == NULL) {

        return -ENOMEM;

    }



    i = elf_ex.e_phnum * sizeof(struct elf_phdr);

    if (elf_ex.e_phoff + i <= BPRM_BUF_SIZE) {

        memcpy(elf_phdata, bprm->buf + elf_ex.e_phoff, i);

    } else {

        retval = pread(bprm->fd, (char *) elf_phdata, i, elf_ex.e_phoff);

        if (retval != i) {

            perror("load_elf_binary");

            exit(-1);

        }

    }

    bswap_phdr(elf_phdata, elf_ex.e_phnum);



    elf_brk = 0;

    elf_stack = ~((abi_ulong)0UL);

    elf_interpreter = NULL;

    start_code = ~((abi_ulong)0UL);

    end_code = 0;

    start_data = 0;

    end_data = 0;

    interp_ex.a_info = 0;



    elf_ppnt = elf_phdata;

    for(i=0;i < elf_ex.e_phnum; i++) {

        if (elf_ppnt->p_type == PT_INTERP) {

            if ( elf_interpreter != NULL )

            {

                free (elf_phdata);

                free(elf_interpreter);

                close(bprm->fd);

                return -EINVAL;

            }



             



            elf_interpreter = (char *)malloc(elf_ppnt->p_filesz);



            if (elf_interpreter == NULL) {

                free (elf_phdata);

                close(bprm->fd);

                return -ENOMEM;

            }



            if (elf_ppnt->p_offset + elf_ppnt->p_filesz <= BPRM_BUF_SIZE) {

                memcpy(elf_interpreter, bprm->buf + elf_ppnt->p_offset,

                       elf_ppnt->p_filesz);

            } else {

                retval = pread(bprm->fd, elf_interpreter, elf_ppnt->p_filesz,

                               elf_ppnt->p_offset);

                if (retval != elf_ppnt->p_filesz) {

                    perror("load_elf_binary2");

                    exit(-1);

                }

            }



             



             



            if (strcmp(elf_interpreter,"/usr/lib/libc.so.1") == 0 ||

                strcmp(elf_interpreter,"/usr/lib/ld.so.1") == 0) {

                ibcs2_interpreter = 1;

            }



            retval = open(path(elf_interpreter), O_RDONLY);

            if (retval < 0) {

                perror(elf_interpreter);

                exit(-1);

            }

            interpreter_fd = retval;



            retval = read(interpreter_fd, bprm->buf, BPRM_BUF_SIZE);

            if (retval < 0) {

                perror("load_elf_binary3");

                exit(-1);

            }

            if (retval < BPRM_BUF_SIZE) {

                memset(bprm->buf, 0, BPRM_BUF_SIZE - retval);

            }



            interp_ex = *((struct exec *) bprm->buf);  

            interp_elf_ex = *((struct elfhdr *) bprm->buf);  

        }

        elf_ppnt++;

    }



     

    if (elf_interpreter){

        interpreter_type = INTERPRETER_ELF | INTERPRETER_AOUT;



         

        if ((N_MAGIC(interp_ex) != OMAGIC) && (N_MAGIC(interp_ex) != ZMAGIC) &&

            (N_MAGIC(interp_ex) != QMAGIC)) {

            interpreter_type = INTERPRETER_ELF;

        }



        if (interp_elf_ex.e_ident[0] != 0x7f ||

            strncmp((char *)&interp_elf_ex.e_ident[1], "ELF",3) != 0) {

            interpreter_type &= ~INTERPRETER_ELF;

        }



        if (!interpreter_type) {

            free(elf_interpreter);

            free(elf_phdata);

            close(bprm->fd);

            return -ELIBBAD;

        }

    }



     



    {

        char * passed_p;



        if (interpreter_type == INTERPRETER_AOUT) {

            snprintf(passed_fileno, sizeof(passed_fileno), "%d", bprm->fd);

            passed_p = passed_fileno;



            if (elf_interpreter) {

                bprm->p = copy_elf_strings(1,&passed_p,bprm->page,bprm->p);

                bprm->argc++;

            }

        }

        if (!bprm->p) {

            if (elf_interpreter) {

                free(elf_interpreter);

            }

            free (elf_phdata);

            close(bprm->fd);

            return -E2BIG;

        }

    }



     

    info->end_data = 0;

    info->end_code = 0;

    info->start_mmap = (abi_ulong)ELF_START_MMAP;

    info->mmap = 0;

    elf_entry = (abi_ulong) elf_ex.e_entry;


     

    if (!(have_guest_base || reserved_va)) {

         

        abi_ulong app_start = ~0;

        abi_ulong app_end = 0;

        abi_ulong addr;

        unsigned long host_start;

        unsigned long real_start;

        unsigned long host_size;

        for (i = 0, elf_ppnt = elf_phdata; i < elf_ex.e_phnum;

             i++, elf_ppnt++) {

            if (elf_ppnt->p_type != PT_LOAD)

                continue;

            addr = elf_ppnt->p_vaddr;

            if (addr < app_start) {

                app_start = addr;

            }

            addr += elf_ppnt->p_memsz;

            if (addr > app_end) {

                app_end = addr;

            }

        }



         

        assert(app_start < app_end);



         

        app_start = app_start & qemu_host_page_mask;

        app_end = HOST_PAGE_ALIGN(app_end);

        if (app_start < mmap_min_addr) {

            host_start = HOST_PAGE_ALIGN(mmap_min_addr);

        } else {

            host_start = app_start;

            if (host_start != app_start) {

                fprintf(stderr, "qemu: Address overflow loading ELF binary\n");

                abort();

            }

        }

        host_size = app_end - app_start;

        while (1) {

             

            real_start = (unsigned long)mmap((void *)host_start, host_size,

                PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0);

            if (real_start == (unsigned long)-1) {

                fprintf(stderr, "qemu: Virtual memory exausted\n");

                abort();

            }

            if (real_start == host_start) {

                break;

            }

             

            munmap((void *)real_start, host_size);

            host_start += qemu_host_page_size;

            if (host_start == app_start) {

                 

                fprintf(stderr, "qemu: Unable to find space for application\n");

                abort();

            }

        }

        qemu_log("Relocating guest address space from 0x" TARGET_ABI_FMT_lx

                 " to 0x%lx\n", app_start, real_start);

        guest_base = real_start - app_start;

    }




     

    info->rss = 0;

    bprm->p = setup_arg_pages(bprm->p, bprm, info);

    info->start_stack = bprm->p;



     



    for(i = 0, elf_ppnt = elf_phdata; i < elf_ex.e_phnum; i++, elf_ppnt++) {

        int elf_prot = 0;

        int elf_flags = 0;

        abi_ulong error;



        if (elf_ppnt->p_type != PT_LOAD)

            continue;



        if (elf_ppnt->p_flags & PF_R) elf_prot |= PROT_READ;

        if (elf_ppnt->p_flags & PF_W) elf_prot |= PROT_WRITE;

        if (elf_ppnt->p_flags & PF_X) elf_prot |= PROT_EXEC;

        elf_flags = MAP_PRIVATE | MAP_DENYWRITE;

        if (elf_ex.e_type == ET_EXEC || load_addr_set) {

            elf_flags |= MAP_FIXED;

        } else if (elf_ex.e_type == ET_DYN) {

             

             

            error = target_mmap(0, ET_DYN_MAP_SIZE,

                                PROT_NONE, MAP_PRIVATE | MAP_ANON,

                                -1, 0);

            if (error == -1) {

                perror("mmap");

                exit(-1);

            }

            load_bias = TARGET_ELF_PAGESTART(error - elf_ppnt->p_vaddr);

        }



        error = target_mmap(TARGET_ELF_PAGESTART(load_bias + elf_ppnt->p_vaddr),

                            (elf_ppnt->p_filesz +

                             TARGET_ELF_PAGEOFFSET(elf_ppnt->p_vaddr)),

                            elf_prot,

                            (MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE),

                            bprm->fd,

                            (elf_ppnt->p_offset -

                             TARGET_ELF_PAGEOFFSET(elf_ppnt->p_vaddr)));

        if (error == -1) {

            perror("mmap");

            exit(-1);

        }


        if (TARGET_ELF_PAGESTART(elf_ppnt->p_vaddr) < elf_stack)

            elf_stack = TARGET_ELF_PAGESTART(elf_ppnt->p_vaddr);




        if (!load_addr_set) {

            load_addr_set = 1;

            load_addr = elf_ppnt->p_vaddr - elf_ppnt->p_offset;

            if (elf_ex.e_type == ET_DYN) {

                load_bias += error -

                    TARGET_ELF_PAGESTART(load_bias + elf_ppnt->p_vaddr);

                load_addr += load_bias;

                reloc_func_desc = load_bias;

            }

        }

        k = elf_ppnt->p_vaddr;

        if (k < start_code)

            start_code = k;

        if (start_data < k)

            start_data = k;

        k = elf_ppnt->p_vaddr + elf_ppnt->p_filesz;

        if ((elf_ppnt->p_flags & PF_X) && end_code <  k)

            end_code = k;

        if (end_data < k)

            end_data = k;

        k = elf_ppnt->p_vaddr + elf_ppnt->p_memsz;

        if (k > elf_brk) {

            elf_brk = TARGET_PAGE_ALIGN(k);

        }



         

        if (elf_ppnt->p_filesz < elf_ppnt->p_memsz) {

            abi_ulong base = load_bias + elf_ppnt->p_vaddr;

            zero_bss(base + elf_ppnt->p_filesz,

                     base + elf_ppnt->p_memsz, elf_prot);

        }

    }



    elf_entry += load_bias;

    elf_brk += load_bias;

    start_code += load_bias;

    end_code += load_bias;

    start_data += load_bias;

    end_data += load_bias;



    if (elf_interpreter) {

        if (interpreter_type & 1) {

            elf_entry = load_aout_interp(&interp_ex, interpreter_fd);

        } else if (interpreter_type & 2) {

            elf_entry = load_elf_interp(&interp_elf_ex, interpreter_fd,

                                        &interp_load_addr, bprm->buf);

        }

        reloc_func_desc = interp_load_addr;



        close(interpreter_fd);

        free(elf_interpreter);



        if (elf_entry == ~((abi_ulong)0UL)) {

            printf("Unable to load interpreter\n");

            free(elf_phdata);

            exit(-1);

            return 0;

        }

    }



    free(elf_phdata);



    if (qemu_log_enabled()) {

        load_symbols(&elf_ex, bprm->fd, load_bias);

    }



    if (interpreter_type != INTERPRETER_AOUT) close(bprm->fd);

    info->personality = (ibcs2_interpreter ? PER_SVR4 : PER_LINUX);


    info->start_stack = bprm->p = elf_stack - 4;


    bprm->p = create_elf_tables(bprm->p,

                                bprm->argc,

                                bprm->envc,

                                &elf_ex,

                                load_addr, load_bias,

                                interp_load_addr,

                                (interpreter_type == INTERPRETER_AOUT ? 0 : 1),

                                info);

    info->load_addr = reloc_func_desc;

    info->start_brk = info->brk = elf_brk;

    info->end_code = end_code;

    info->start_code = start_code;

    info->start_data = start_data;

    info->end_data = end_data;

    info->start_stack = bprm->p;


    printf("(start_brk) %x\n" , info->start_brk);

    printf("(end_code) %x\n" , info->end_code);

    printf("(start_code) %x\n" , info->start_code);

    printf("(end_data) %x\n" , info->end_data);

    printf("(start_stack) %x\n" , info->start_stack);

    printf("(brk) %x\n" , info->brk);




    if ( info->personality == PER_SVR4 )

    {

         

        mapped_addr = target_mmap(0, qemu_host_page_size, PROT_READ | PROT_EXEC,

                                  MAP_FIXED | MAP_PRIVATE, -1, 0);

    }



    info->entry = elf_entry;


    bprm->core_dump = &elf_core_dump;




    return 0;

}
