/******************************************************************************
 *
 * Module Name: asloptions - compiler command line processing
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2017, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights. You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code. No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision. In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change. Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee. Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution. In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE. ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES. INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS. INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government. In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************
 *
 * Alternatively, you may choose to be licensed under the terms of the
 * following license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Alternatively, you may choose to be licensed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 *****************************************************************************/

#include <contrib/dev/acpica/compiler/aslcompiler.h>
#include <contrib/dev/acpica/include/acapps.h>
#include <contrib/dev/acpica/include/acdisasm.h>

#define _COMPONENT          ACPI_COMPILER
        ACPI_MODULE_NAME    ("asloption")


/* Local prototypes */

static int
AslDoOptions (
    int                     argc,
    char                    **argv,
    BOOLEAN                 IsResponseFile);

static void
AslMergeOptionTokens (
    char                    *InBuffer,
    char                    *OutBuffer);

static int
AslDoResponseFile (
    char                    *Filename);


#define ASL_TOKEN_SEPARATORS    " \t\n"
#define ASL_SUPPORTED_OPTIONS   "@:a:b|c|d^D:e:f^gh^i|I:l^m:no|p:P^q^r:s|t|T+G^v^w|x:z"


/*******************************************************************************
 *
 * FUNCTION:    AslCommandLine
 *
 * PARAMETERS:  argc/argv
 *
 * RETURN:      Last argv index
 *
 * DESCRIPTION: Command line processing
 *
 ******************************************************************************/

int
AslCommandLine (
    int                     argc,
    char                    **argv)
{
    int                     BadCommandLine = 0;
    ACPI_STATUS             Status;


    /* Minimum command line contains at least the command and an input file */

    if (argc < 2)
    {
        printf (ACPI_COMMON_SIGNON (ASL_COMPILER_NAME));
        Usage ();
        exit (1);
    }

    /* Process all command line options */

    BadCommandLine = AslDoOptions (argc, argv, FALSE);

    if (Gbl_DoTemplates)
    {
        Status = DtCreateTemplates (argv);
        if (ACPI_FAILURE (Status))
        {
            exit (-1);
        }
        exit (1);
    }

    /* Next parameter must be the input filename */

    if (!argv[AcpiGbl_Optind] &&
        !AcpiGbl_DisasmFlag)
    {
        printf ("Missing input filename\n");
        BadCommandLine = TRUE;
    }

    if (Gbl_DoSignon)
    {
        printf (ACPI_COMMON_SIGNON (ASL_COMPILER_NAME));
        if (Gbl_IgnoreErrors)
        {
            printf ("Ignoring all errors, forcing AML file generation\n\n");
        }
    }

    if (BadCommandLine)
    {
        printf ("Use -h option for help information\n");
        exit (1);
    }

    return (AcpiGbl_Optind);
}


/*******************************************************************************
 *
 * FUNCTION:    AslDoOptions
 *
 * PARAMETERS:  argc/argv           - Standard argc/argv
 *              IsResponseFile      - TRUE if executing a response file.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Command line option processing
 *
 ******************************************************************************/

static int
AslDoOptions (
    int                     argc,
    char                    **argv,
    BOOLEAN                 IsResponseFile)
{
    ACPI_STATUS             Status;
    UINT32                  j;


    /* Get the command line options */

    while ((j = AcpiGetopt (argc, argv, ASL_SUPPORTED_OPTIONS)) != ACPI_OPT_END) switch (j)
    {
    case '@':   /* Begin a response file */

        if (IsResponseFile)
        {
            printf ("Nested command files are not supported\n");
            return (-1);
        }

        if (AslDoResponseFile (AcpiGbl_Optarg))
        {
            return (-1);
        }
        break;

    case 'a':   /* Debug options */

        switch (AcpiGbl_Optarg[0])
        {
        case 'r':

            Gbl_EnableReferenceTypechecking = TRUE;
            break;

        default:

            printf ("Unknown option: -a%s\n", AcpiGbl_Optarg);
            return (-1);
        }

        break;


    case 'b':   /* Debug options */

        switch (AcpiGbl_Optarg[0])
        {

        case 'c':

            printf ("Debug ASL to ASL+ conversion\n");

            Gbl_DoAslConversion = TRUE;
            Gbl_FoldConstants = FALSE;
            Gbl_IntegerOptimizationFlag = FALSE;
            Gbl_ReferenceOptimizationFlag = FALSE;
            Gbl_OptimizeTrivialParseNodes = FALSE;
            Gbl_CaptureComments = TRUE;
            AcpiGbl_DoDisassemblerOptimizations = FALSE;
            AcpiGbl_DebugAslConversion = TRUE;
            AcpiGbl_DmEmitExternalOpcodes = TRUE;
            Gbl_DoExternalsInPlace = TRUE;

            return (0);

        case 'f':

            AslCompilerdebug = 1; /* same as yydebug */
            DtParserdebug = 1;
            PrParserdebug = 1;
            Gbl_DebugFlag = TRUE;
            Gbl_KeepPreprocessorTempFile = TRUE;
            break;

        case 'p':   /* Prune ASL parse tree */

            /* Get the required argument */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Gbl_PruneParseTree = TRUE;
            Gbl_PruneDepth = (UINT8) strtoul (AcpiGbl_Optarg, NULL, 0);
            break;

        case 's':

            Gbl_DebugFlag = TRUE;
            break;

        case 't':

            /* Get the required argument */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Gbl_PruneType = (UINT8) strtoul (AcpiGbl_Optarg, NULL, 0);
            break;

        default:

            printf ("Unknown option: -b%s\n", AcpiGbl_Optarg);
            return (-1);
        }

        break;

    case 'c':

        switch (AcpiGbl_Optarg[0])
        {

        case 'a':

            printf ("Convert ASL to ASL+ with comments\n");
            Gbl_DoAslConversion = TRUE;
            Gbl_FoldConstants = FALSE;
            Gbl_IntegerOptimizationFlag = FALSE;
            Gbl_ReferenceOptimizationFlag = FALSE;
            Gbl_OptimizeTrivialParseNodes = FALSE;
            Gbl_CaptureComments = TRUE;
            AcpiGbl_DoDisassemblerOptimizations = FALSE;
            AcpiGbl_DmEmitExternalOpcodes = TRUE;
            Gbl_DoExternalsInPlace = TRUE;

            return (0);

        case 'r':

            Gbl_NoResourceChecking = TRUE;
            break;

        default:

            printf ("Unknown option: -c%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'd':   /* Disassembler */

        switch (AcpiGbl_Optarg[0])
        {
        case '^':

            /* Get the required argument */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Gbl_DoCompile = FALSE;
            break;

        case 'a':

            /* Get the required argument */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Gbl_DoCompile = FALSE;
            Gbl_DisassembleAll = TRUE;
            break;

        case 'b':   /* Do not convert buffers to resource descriptors */

            AcpiGbl_NoResourceDisassembly = TRUE;
            break;

        case 'c':

            break;

        case 'f':

            AcpiGbl_ForceAmlDisassembly = TRUE;
            break;

        case 'l':   /* Use legacy ASL code (not ASL+) for disassembly */

            Gbl_DoCompile = FALSE;
            AcpiGbl_CstyleDisassembly = FALSE;
            break;

        default:

            printf ("Unknown option: -d%s\n", AcpiGbl_Optarg);
            return (-1);
        }

        AcpiGbl_DisasmFlag = TRUE;
        break;

    case 'D':   /* Define a symbol */

        PrAddDefine (AcpiGbl_Optarg, NULL, TRUE);
        break;

    case 'e':   /* External files for disassembler */

        /* Get entire list of external files */

        AcpiGbl_Optind--;
        argv[AcpiGbl_Optind] = AcpiGbl_Optarg;

        while (argv[AcpiGbl_Optind] &&
              (argv[AcpiGbl_Optind][0] != '-'))
        {
            Status = AcpiDmAddToExternalFileList (argv[AcpiGbl_Optind]);
            if (ACPI_FAILURE (Status))
            {
                printf ("Could not add %s to external list\n",
                    argv[AcpiGbl_Optind]);
                return (-1);
            }

            AcpiGbl_Optind++;
        }
        break;

    case 'f':

        switch (AcpiGbl_Optarg[0])
        {
        case '^':   /* Ignore errors and force creation of aml file */

            Gbl_IgnoreErrors = TRUE;
            break;

        case 'e':   /* Disassembler: Get external declaration file */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Gbl_ExternalRefFilename = AcpiGbl_Optarg;
            break;

        default:

            printf ("Unknown option: -f%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'G':

        Gbl_CompileGeneric = TRUE;
        break;

    case 'g':   /* Get all ACPI tables */

        printf ("-g option is deprecated, use acpidump utility instead\n");
        exit (1);

    case 'h':

        switch (AcpiGbl_Optarg[0])
        {
        case '^':

            printf (ACPI_COMMON_SIGNON (ASL_COMPILER_NAME));
            Usage ();
            exit (0);

        case 'c':

            UtDisplayConstantOpcodes ();
            exit (0);

        case 'd':

            AslDisassemblyHelp ();
            exit (0);

        case 'f':

            AslFilenameHelp ();
            exit (0);

        case 'r':

            /* reserved names */

            ApDisplayReservedNames ();
            exit (0);

        case 't':

            UtDisplaySupportedTables ();
            exit (0);

        default:

            printf ("Unknown option: -h%s\n", AcpiGbl_Optarg);
            return (-1);
        }

    case 'I':   /* Add an include file search directory */

        FlAddIncludeDirectory (AcpiGbl_Optarg);
        break;

    case 'i':   /* Output AML as an include file */

        switch (AcpiGbl_Optarg[0])
        {
        case 'a':

            /* Produce assembly code include file */

            Gbl_AsmIncludeOutputFlag = TRUE;
            break;

        case 'c':

            /* Produce C include file */

            Gbl_C_IncludeOutputFlag = TRUE;
            break;

        case 'n':

            /* Compiler/Disassembler: Ignore the NOOP operator */

            AcpiGbl_IgnoreNoopOperator = TRUE;
            break;

        default:

            printf ("Unknown option: -i%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'l':   /* Listing files */

        switch (AcpiGbl_Optarg[0])
        {
        case '^':

            /* Produce listing file (Mixed source/aml) */

            Gbl_ListingFlag = TRUE;
            AcpiGbl_DmOpt_Listing = TRUE;
            break;

        case 'i':

            /* Produce preprocessor output file */

            Gbl_PreprocessorOutputFlag = TRUE;
            break;

        case 'm':

            /* Produce hardware map summary file */

            Gbl_MapfileFlag = TRUE;
            break;

        case 'n':

            /* Produce namespace file */

            Gbl_NsOutputFlag = TRUE;
            break;

        case 's':

            /* Produce combined source file */

            Gbl_SourceOutputFlag = TRUE;
            break;

        case 'x':

            /* Produce cross-reference file */

            Gbl_CrossReferenceOutput = TRUE;
            break;

        default:

            printf ("Unknown option: -l%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'm':   /* Set line buffer size */

        Gbl_LineBufferSize = (UINT32) strtoul (AcpiGbl_Optarg, NULL, 0) * 1024;
        if (Gbl_LineBufferSize < ASL_DEFAULT_LINE_BUFFER_SIZE)
        {
            Gbl_LineBufferSize = ASL_DEFAULT_LINE_BUFFER_SIZE;
        }
        printf ("Line Buffer Size: %u\n", Gbl_LineBufferSize);
        break;

    case 'n':   /* Parse only */

        Gbl_ParseOnlyFlag = TRUE;
        break;

    case 'o':   /* Control compiler AML optimizations */

        switch (AcpiGbl_Optarg[0])
        {
        case 'a':

            /* Disable all optimizations */

            Gbl_FoldConstants = FALSE;
            Gbl_IntegerOptimizationFlag = FALSE;
            Gbl_ReferenceOptimizationFlag = FALSE;
            Gbl_OptimizeTrivialParseNodes = FALSE;

            break;

        case 'c':

            /* Display compile time(s) */

            Gbl_CompileTimesFlag = TRUE;
            break;

        case 'd':

            /* Disable disassembler code optimizations */

            AcpiGbl_DoDisassemblerOptimizations = FALSE;
            break;

        case 'e':

            /* Disassembler: Emit embedded external operators */

            AcpiGbl_DmEmitExternalOpcodes = TRUE;
            break;

        case 'E':

            /*
             * iASL: keep External opcodes in place.
             * No affect if Gbl_DoExternals is false.
             */

            Gbl_DoExternalsInPlace = TRUE;
            break;

        case 'f':

            /* Disable folding on "normal" expressions */

            Gbl_FoldConstants = FALSE;
            break;

        case 'i':

            /* Disable integer optimization to constants */

            Gbl_IntegerOptimizationFlag = FALSE;
            break;

        case 'n':

            /* Disable named reference optimization */

            Gbl_ReferenceOptimizationFlag = FALSE;
            break;

        case 't':

            /* Disable heavy typechecking */

            Gbl_DoTypechecking = FALSE;
            break;

        default:

            printf ("Unknown option: -c%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'P':   /* Preprocessor options */

        switch (AcpiGbl_Optarg[0])
        {
        case '^':   /* Proprocess only, emit (.i) file */

            Gbl_PreprocessOnly = TRUE;
            Gbl_PreprocessorOutputFlag = TRUE;
            break;

        case 'n':   /* Disable preprocessor */

            Gbl_PreprocessFlag = FALSE;
            break;

        default:

            printf ("Unknown option: -P%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'p':   /* Override default AML output filename */

        Gbl_OutputFilenamePrefix = AcpiGbl_Optarg;
        UtConvertBackslashes (Gbl_OutputFilenamePrefix);
        Gbl_UseDefaultAmlFilename = FALSE;
        break;

    case 'q':   /* ASL/ASl+ converter: compile only and leave badaml. */

        printf ("Convert ASL to ASL+ with comments\n");
        Gbl_FoldConstants = FALSE;
        Gbl_IntegerOptimizationFlag = FALSE;
        Gbl_ReferenceOptimizationFlag = FALSE;
        Gbl_OptimizeTrivialParseNodes = FALSE;
        Gbl_CaptureComments = TRUE;
        Gbl_DoExternalsInPlace = TRUE;
        return (0);

    case 'r':   /* Override revision found in table header */

        Gbl_RevisionOverride = (UINT8) strtoul (AcpiGbl_Optarg, NULL, 0);
        break;

    case 's':   /* Create AML in a source code file */

        switch (AcpiGbl_Optarg[0])
        {
        case 'a':

            /* Produce assembly code output file */

            Gbl_AsmOutputFlag = TRUE;
            break;

        case 'c':

            /* Produce C hex output file */

            Gbl_C_OutputFlag = TRUE;
            break;

        case 'o':

            /* Produce AML offset table in C */

            Gbl_C_OffsetTableFlag = TRUE;
            break;

        default:

            printf ("Unknown option: -s%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 't':   /* Produce hex table output file */

        switch (AcpiGbl_Optarg[0])
        {
        case 'a':

            Gbl_HexOutputFlag = HEX_OUTPUT_ASM;
            break;

        case 'c':

            Gbl_HexOutputFlag = HEX_OUTPUT_C;
            break;

        case 's':

            Gbl_HexOutputFlag = HEX_OUTPUT_ASL;
            break;

        default:

            printf ("Unknown option: -t%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'T':   /* Create a ACPI table template file */

        Gbl_DoTemplates = TRUE;
        break;

    case 'v':   /* Version and verbosity settings */

        switch (AcpiGbl_Optarg[0])
        {
        case '^':

            printf (ACPI_COMMON_SIGNON (ASL_COMPILER_NAME));
            exit (0);

        case 'a':

            /* Disable all error/warning/remark messages */

            Gbl_NoErrors = TRUE;
            break;

        case 'e':

            /* Disable all warning/remark messages (errors only) */

            Gbl_DisplayRemarks = FALSE;
            Gbl_DisplayWarnings = FALSE;
            break;

        case 'i':
            /*
             * Support for integrated development environment(s).
             *
             * 1) No compiler signon
             * 2) Send stderr messages to stdout
             * 3) Less verbose error messages (single line only for each)
             * 4) Error/warning messages are formatted appropriately to
             *    be recognized by MS Visual Studio
             */
            Gbl_VerboseErrors = FALSE;
            Gbl_DoSignon = FALSE;
            Gbl_Files[ASL_FILE_STDERR].Handle = stdout;
            break;

        case 'o':

            Gbl_DisplayOptimizations = TRUE;
            break;

        case 'r':

            Gbl_DisplayRemarks = FALSE;
            break;

        case 's':

            Gbl_DoSignon = FALSE;
            break;

        case 't':

            Gbl_VerboseTemplates = TRUE;
            break;

        case 'w':

            /* Get the required argument */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Status = AslDisableException (AcpiGbl_Optarg);
            if (ACPI_FAILURE (Status))
            {
                return (-1);
            }
            break;

        case 'x':

            /* Get the required argument */

            if (AcpiGetoptArgument (argc, argv))
            {
                return (-1);
            }

            Status = AslExpectException (AcpiGbl_Optarg);
            if (ACPI_FAILURE (Status))
            {
                return (-1);
            }
            break;

        default:

            printf ("Unknown option: -v%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'w': /* Set warning levels */

        switch (AcpiGbl_Optarg[0])
        {
        case '1':

            Gbl_WarningLevel = ASL_WARNING;
            break;

        case '2':

            Gbl_WarningLevel = ASL_WARNING2;
            break;

        case '3':

            Gbl_WarningLevel = ASL_WARNING3;
            break;

        case 'e':

            Gbl_WarningsAsErrors = TRUE;
            break;

        default:

            printf ("Unknown option: -w%s\n", AcpiGbl_Optarg);
            return (-1);
        }
        break;

    case 'x':   /* Set debug print output level */

        AcpiDbgLevel = strtoul (AcpiGbl_Optarg, NULL, 16);
        break;

    case 'z':

        Gbl_UseOriginalCompilerId = TRUE;
        break;

    default:

        return (-1);
    }

    return (0);
}


/*******************************************************************************
 *
 * FUNCTION:    AslMergeOptionTokens
 *
 * PARAMETERS:  InBuffer            - Input containing an option string
 *              OutBuffer           - Merged output buffer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Remove all whitespace from an option string.
 *
 ******************************************************************************/

static void
AslMergeOptionTokens (
    char                    *InBuffer,
    char                    *OutBuffer)
{
    char                    *Token;


    *OutBuffer = 0;

    Token = strtok (InBuffer, ASL_TOKEN_SEPARATORS);
    while (Token)
    {
        strcat (OutBuffer, Token);
        Token = strtok (NULL, ASL_TOKEN_SEPARATORS);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AslDoResponseFile
 *
 * PARAMETERS:  Filename        - Name of the response file
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Open a response file and process all options within.
 *
 ******************************************************************************/

static int
AslDoResponseFile (
    char                    *Filename)
{
    char                    *argv = StringBuffer2;
    FILE                    *ResponseFile;
    int                     OptStatus = 0;
    int                     Opterr;
    int                     Optind;


    ResponseFile = fopen (Filename, "r");
    if (!ResponseFile)
    {
        printf ("Could not open command file %s, %s\n",
            Filename, strerror (errno));
        return (-1);
    }

    /* Must save the current GetOpt globals */

    Opterr = AcpiGbl_Opterr;
    Optind = AcpiGbl_Optind;

    /*
     * Process all lines in the response file. There must be one complete
     * option per line
     */
    while (fgets (StringBuffer, ASL_MSG_BUFFER_SIZE, ResponseFile))
    {
        /* Compress all tokens, allowing us to use a single argv entry */

        AslMergeOptionTokens (StringBuffer, StringBuffer2);

        /* Process the option */

        AcpiGbl_Opterr = 0;
        AcpiGbl_Optind = 0;

        OptStatus = AslDoOptions (1, &argv, TRUE);
        if (OptStatus)
        {
            printf ("Invalid option in command file %s: %s\n",
                Filename, StringBuffer);
            break;
        }
    }

    /* Restore the GetOpt globals */

    AcpiGbl_Opterr = Opterr;
    AcpiGbl_Optind = Optind;

    fclose (ResponseFile);
    return (OptStatus);
}
