#ifndef _CCTX_COMPILER_H
#define _CCTX_COMPILER_H
#pragma once

// Compiler
//	CCTX_COMPILER_CLANG Clang
//	CCTX_COMPILER_LLVM_CLANG LLVM-Clang
//	CCTX_COMPILER_GCC GCC
//	CCTX_COMPILER_LLVM_GCC LLVM-GCC
//	CCTX_COMPILER_MSC Microsoft Visual C++
//	CCTX_COMPILER_BTC Borland Turbo C http://cc.embarcadero.com/item/25636
//	CCTX_COMPILER_BC Borland C https://www.embarcadero.com/free-tools/ccompiler
//	CCTX_COMPILER_BCPP Borland C++ https://www.embarcadero.com/free-tools/ccompiler
//	CCTX_COMPILER_SNC SN
//	CCTX_COMPILER_MWC Metrowerks CodeWarrior https://www.nxp.com/support/developer-resources/software-development-tools/codewarrior-development-tools:CW_HOME
//	CCTX_COMPILER_CVC Codeplay VectorC https://www.codeplay.com/company/documents/vectorc-compiler-engine.html
//	CCTX_COMPILER_CYGWIN Cygwin http://www.cygwin.com/
//	CCTX_COMPILER_COMO Comeau C++ http://www.comeaucomputing.com/
//	CCTX_COMPILER_ICL Intel C++ https://software.intel.com/en-us/intel-sdp-home
//	CCTX_COMPILER_DMC Digital Mars
//	CCTX_COMPILER_DECC Compaq C
//	CCTX_COMPILER_DECCPP Compaq C++ http://www.cism.ucl.ac.be/Equipements/Logiciels/Manuels/Compaq/C++/ugu/u57.htm
//	CCTX_COMPILER_COV Coverity C/C++ Static Analyzer
//	CCTX_COMPILER_DIAB Diab C/C++ https://www.windriver.com/products/development-tools/
//	CCTX_COMPILER_IMGC ImageCraft C
//	CCTX_COMPILER_CARM KEIL CARM
//	CCTX_COMPILER_C166 KEIL C166
//	CCTX_COMPILER_C51 KEIL C51
//	CCTX_COMPILER_LLVM LLVM
//	CCTX_COMPILER_HIGHC MetaWare High C/C++
//	CCTX_COMPILER_MRI Microtec C/C++
//	CCTX_COMPILER_MINGW32 MinGW http://www.mingw.org/
//	CCTX_COMPILER_MINGW64 MinGW http://www.mingw.org/
//	CCTX_COMPILER_SPC Solaris Studio C https://www.oracle.com/sun/index.html
//	CCTX_COMPILER_SPCPP Solaris Studio C++ https://www.oracle.com/sun/index.html
//	CCTX_COMPILER_IBMC IBM XL C http://www.ibm.com/software/ad/caix/
//	CCTX_COMPILER_IBMCPP IBM XL C++ http://www.ibm.com/software/ad/caix/
//	CCTX_COMPILER_PGI Portland Group PGI PGCC/PGPP
//	CCTX_COMPILER_HPC HP C http://devresource.hp.com/devresource/Tools/lang.html
//	CCTX_COMPILER_HPCPP HP aC++ http://devresource.hp.com/devresource/Tools/lang.html
//	CCTX_COMPILER_CRAYC Cray C/C++ http://www.cray.com/products/software/cplus.html
//	CCTX_COMPILER_KCC KAI C++ http://developer.intel.com/software/products/kcc/
//	CCTX_COMPILER_NC Norcroft C http://www.codemist.co.uk/ncc/index.html
//	CCTX_COMPILER_TC Tiny C https://bellard.org/tcc/
//	CCTX_COMPILER_USLC USL C https://bellard.org/tcc/
//	CCTX_COMPILER_WC Watcom C++ http://openwatcom.com/
//	CCTX_COMPILER_SASC SAS/C https://www.sas.com
//	CCTX_COMPILER_CG CodeGear
//	CCTX_COMPILER_GHS Greenhills C++
//	CCTX_COMPILER_SGI SGI MIPSpro C++
//	CCTX_COMPILER_MSC Microsoft Visual Studio Compiler

#if (defined __clang__) // Clang defines __GNUC__
#	define CCTX_COMPILER_CLANG
#	if (defined __llvm__)
#		define CCTX_COMPILER_LLVM_CLANG
#	endif
#elif ((defined __INTEL_COMPILER) || (defined __ICL)) // ILC defines __GNUC__
#	define CCTX_COMPILER_ICL
#elif (defined __MINGW32__) // MinGW32 defines __GNUC__
#	define CCTX_COMPILER_MINGW32
#elif (defined __MINGW64__) // MinGW64 defines __GNUC__
#	define CCTX_COMPILER_MINGW64
#elif ((defined __GNUC__) || (defined __GCC__))
#	define CCTX_COMPILER_GCC
#elif (defined __CODEGEARC__ ) // MinGW64 defines __BORLANDC__
#	define CCTX_COMPILER_CG
#elif (defined __TURBOC__ )
#	define CCTX_COMPILER_BTC
#elif ((defined __BORLANDC) || (defined __BORLANDC__)) // __BCPLUSPLUS__ also defines __BORLANDC__
#	define CCTX_COMPILER_BC
#elif (defined __BCPLUSPLUS__)
#	define CCTX_COMPILER_BCPP
#elif (defined __SNC__)
#	define CCTX_COMPILER_SNC
#elif ((defined __MWERKS__) || (defined __CWCC__))
#	define CCTX_COMPILER_MWC
#elif (defined __VECTOR_C)
#	define CCTX_COMPILER_CVC
#elif (defined __CYGWIN__)
#	define CCTX_COMPILER_CYGWIN
#elif (defined __COMO__)
#	define CCTX_COMPILER_COMO
#elif (defined __DMC__)
#	define CCTX_COMPILER_DMC
#elif (defined __DECC)
#	define CCTX_COMPILER_DECC
#elif (defined __DECCXX)
#	define CCTX_COMPILER_DECCPP
#elif (defined __COVERITY__)
#	define CCTX_COMPILER_COV
#elif (defined __DCC__)
#	define CCTX_COMPILER_DIAB
#elif (defined __IMAGECRAFT__)
#	define CCTX_COMPILER_IMGC
#elif (defined __CA__)
#	define CCTX_COMPILER_CARM
#elif (defined __C166__)
#	define CCTX_COMPILER_C166
#elif (defined __C51__)
#	define CCTX_COMPILER_C51
#elif (defined __llvm__)
#	define CCTX_COMPILER_LLVM
#elif (defined __HIGHC__)
#	define CCTX_COMPILER_HIGHC
#elif (defined _MRI)
#	define CCTX_COMPILER_MRI
#elif (defined __SUNPRO_C)
#	define CCTX_COMPILER_SPC
#elif (defined __SUNPRO_CC)
#	define CCTX_COMPILER_SPCPP
#elif (defined __IBMC__)
#	define CCTX_COMPILER_IBMC
#elif (defined __IBMCPP__)
#	define CCTX_COMPILER_IBMCPP
#elif (defined __PGI)
#	define CCTX_COMPILER_PGI
#elif (defined __HP_cc)
#	define CCTX_COMPILER_HPC
#elif (defined __HP_aCC)
#	define CCTX_COMPILER_HPCPP
#elif (defined _CRAYC)
#	define CCTX_COMPILER_CRAYC
#elif (defined __KCC)
#	define CCTX_COMPILER_KCC
#elif (defined __CC_NORCROFT)
#	define CCTX_COMPILER_NC
#elif (defined __TINYC__)
#	define CCTX_COMPILER_TC
#elif (defined __USLC__)
#	define CCTX_COMPILER_USLC
#elif (defined __WATCOMC__)
#	define CCTX_COMPILER_WC
#elif ((defined __SASC__) || (defined __SASC))
#	define CCTX_COMPILER_SASC
#elif (defined _MSC_VER)
#	define CCTX_COMPILER_MSC
#elif (defined __ghs)
#	define CCTX_COMPILER_GHS
#elif (defined __sgi)
#	define CCTX_COMPILER_SGI
#else
#	error unsupported compiler
#endif

#endif // _CCTX_COMPILER_H
