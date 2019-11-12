#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/SqLite/sqlite3.o \
	${OBJECTDIR}/base64/base64_api.o \
	${OBJECTDIR}/base64/base64_lib.o \
	${OBJECTDIR}/file/file_api.o \
	${OBJECTDIR}/file/file_lib.o \
	${OBJECTDIR}/html2txt/html2txt_api.o \
	${OBJECTDIR}/html2txt/html2txt_lib.o \
	${OBJECTDIR}/list/list_api.o \
	${OBJECTDIR}/list/list_lib.o \
	${OBJECTDIR}/log/log_api.o \
	${OBJECTDIR}/log/log_lib.o \
	${OBJECTDIR}/mem/mem_api.o \
	${OBJECTDIR}/mem/mem_lib.o \
	${OBJECTDIR}/queue/queue_api.o \
	${OBJECTDIR}/queue/queue_lib.o \
	${OBJECTDIR}/sha1/sha1_api.o \
	${OBJECTDIR}/sha1/sha1_lib.o \
	${OBJECTDIR}/store/store_api.o \
	${OBJECTDIR}/store/store_lib.o \
	${OBJECTDIR}/tcpip/tcpip_api.o \
	${OBJECTDIR}/tcpip/tcpip_lib.o \
	${OBJECTDIR}/text/text_api.o \
	${OBJECTDIR}/text/text_lib.o \
	${OBJECTDIR}/thread/thread_api.o \
	${OBJECTDIR}/thread/thread_lib.o \
	${OBJECTDIR}/token/token_api.o \
	${OBJECTDIR}/token/token_lib.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/file/tests/TEST__text_atox.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibtools.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibtools.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibtools.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibtools.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibtools.a

${OBJECTDIR}/SqLite/sqlite3.o: SqLite/sqlite3.c
	${MKDIR} -p ${OBJECTDIR}/SqLite
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SqLite/sqlite3.o SqLite/sqlite3.c

${OBJECTDIR}/base64/base64_api.o: base64/base64_api.c
	${MKDIR} -p ${OBJECTDIR}/base64
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base64/base64_api.o base64/base64_api.c

${OBJECTDIR}/base64/base64_lib.o: base64/base64_lib.c
	${MKDIR} -p ${OBJECTDIR}/base64
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base64/base64_lib.o base64/base64_lib.c

${OBJECTDIR}/file/file_api.o: file/file_api.c
	${MKDIR} -p ${OBJECTDIR}/file
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file/file_api.o file/file_api.c

${OBJECTDIR}/file/file_lib.o: file/file_lib.c
	${MKDIR} -p ${OBJECTDIR}/file
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file/file_lib.o file/file_lib.c

${OBJECTDIR}/html2txt/html2txt_api.o: html2txt/html2txt_api.c
	${MKDIR} -p ${OBJECTDIR}/html2txt
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/html2txt/html2txt_api.o html2txt/html2txt_api.c

${OBJECTDIR}/html2txt/html2txt_lib.o: html2txt/html2txt_lib.c
	${MKDIR} -p ${OBJECTDIR}/html2txt
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/html2txt/html2txt_lib.o html2txt/html2txt_lib.c

${OBJECTDIR}/list/list_api.o: list/list_api.c
	${MKDIR} -p ${OBJECTDIR}/list
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/list/list_api.o list/list_api.c

${OBJECTDIR}/list/list_lib.o: list/list_lib.c
	${MKDIR} -p ${OBJECTDIR}/list
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/list/list_lib.o list/list_lib.c

${OBJECTDIR}/log/log_api.o: log/log_api.c
	${MKDIR} -p ${OBJECTDIR}/log
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log/log_api.o log/log_api.c

${OBJECTDIR}/log/log_lib.o: log/log_lib.c
	${MKDIR} -p ${OBJECTDIR}/log
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log/log_lib.o log/log_lib.c

${OBJECTDIR}/mem/mem_api.o: mem/mem_api.c
	${MKDIR} -p ${OBJECTDIR}/mem
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mem/mem_api.o mem/mem_api.c

${OBJECTDIR}/mem/mem_lib.o: mem/mem_lib.c
	${MKDIR} -p ${OBJECTDIR}/mem
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mem/mem_lib.o mem/mem_lib.c

${OBJECTDIR}/queue/queue_api.o: queue/queue_api.c
	${MKDIR} -p ${OBJECTDIR}/queue
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/queue/queue_api.o queue/queue_api.c

${OBJECTDIR}/queue/queue_lib.o: queue/queue_lib.c
	${MKDIR} -p ${OBJECTDIR}/queue
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/queue/queue_lib.o queue/queue_lib.c

${OBJECTDIR}/sha1/sha1_api.o: sha1/sha1_api.c
	${MKDIR} -p ${OBJECTDIR}/sha1
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sha1/sha1_api.o sha1/sha1_api.c

${OBJECTDIR}/sha1/sha1_lib.o: sha1/sha1_lib.c
	${MKDIR} -p ${OBJECTDIR}/sha1
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sha1/sha1_lib.o sha1/sha1_lib.c

${OBJECTDIR}/store/store_api.o: store/store_api.c
	${MKDIR} -p ${OBJECTDIR}/store
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/store/store_api.o store/store_api.c

${OBJECTDIR}/store/store_lib.o: store/store_lib.c
	${MKDIR} -p ${OBJECTDIR}/store
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/store/store_lib.o store/store_lib.c

${OBJECTDIR}/tcpip/tcpip_api.o: tcpip/tcpip_api.c
	${MKDIR} -p ${OBJECTDIR}/tcpip
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcpip/tcpip_api.o tcpip/tcpip_api.c

${OBJECTDIR}/tcpip/tcpip_lib.o: tcpip/tcpip_lib.c
	${MKDIR} -p ${OBJECTDIR}/tcpip
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcpip/tcpip_lib.o tcpip/tcpip_lib.c

${OBJECTDIR}/text/text_api.o: text/text_api.c
	${MKDIR} -p ${OBJECTDIR}/text
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/text/text_api.o text/text_api.c

${OBJECTDIR}/text/text_lib.o: text/text_lib.c
	${MKDIR} -p ${OBJECTDIR}/text
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/text/text_lib.o text/text_lib.c

${OBJECTDIR}/thread/thread_api.o: thread/thread_api.c
	${MKDIR} -p ${OBJECTDIR}/thread
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thread/thread_api.o thread/thread_api.c

${OBJECTDIR}/thread/thread_lib.o: thread/thread_lib.c
	${MKDIR} -p ${OBJECTDIR}/thread
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thread/thread_lib.o thread/thread_lib.c

${OBJECTDIR}/token/token_api.o: token/token_api.c
	${MKDIR} -p ${OBJECTDIR}/token
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/token/token_api.o token/token_api.c

${OBJECTDIR}/token/token_lib.o: token/token_lib.c
	${MKDIR} -p ${OBJECTDIR}/token
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/token/token_lib.o token/token_lib.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/file/tests/TEST__text_atox.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/file/tests/TEST__text_atox.o: file/tests/TEST__text_atox.c 
	${MKDIR} -p ${TESTDIR}/file/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/file/tests/TEST__text_atox.o file/tests/TEST__text_atox.c


${OBJECTDIR}/SqLite/sqlite3_nomain.o: ${OBJECTDIR}/SqLite/sqlite3.o SqLite/sqlite3.c 
	${MKDIR} -p ${OBJECTDIR}/SqLite
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SqLite/sqlite3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SqLite/sqlite3_nomain.o SqLite/sqlite3.c;\
	else  \
	    ${CP} ${OBJECTDIR}/SqLite/sqlite3.o ${OBJECTDIR}/SqLite/sqlite3_nomain.o;\
	fi

${OBJECTDIR}/base64/base64_api_nomain.o: ${OBJECTDIR}/base64/base64_api.o base64/base64_api.c 
	${MKDIR} -p ${OBJECTDIR}/base64
	@NMOUTPUT=`${NM} ${OBJECTDIR}/base64/base64_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base64/base64_api_nomain.o base64/base64_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/base64/base64_api.o ${OBJECTDIR}/base64/base64_api_nomain.o;\
	fi

${OBJECTDIR}/base64/base64_lib_nomain.o: ${OBJECTDIR}/base64/base64_lib.o base64/base64_lib.c 
	${MKDIR} -p ${OBJECTDIR}/base64
	@NMOUTPUT=`${NM} ${OBJECTDIR}/base64/base64_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base64/base64_lib_nomain.o base64/base64_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/base64/base64_lib.o ${OBJECTDIR}/base64/base64_lib_nomain.o;\
	fi

${OBJECTDIR}/file/file_api_nomain.o: ${OBJECTDIR}/file/file_api.o file/file_api.c 
	${MKDIR} -p ${OBJECTDIR}/file
	@NMOUTPUT=`${NM} ${OBJECTDIR}/file/file_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file/file_api_nomain.o file/file_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/file/file_api.o ${OBJECTDIR}/file/file_api_nomain.o;\
	fi

${OBJECTDIR}/file/file_lib_nomain.o: ${OBJECTDIR}/file/file_lib.o file/file_lib.c 
	${MKDIR} -p ${OBJECTDIR}/file
	@NMOUTPUT=`${NM} ${OBJECTDIR}/file/file_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file/file_lib_nomain.o file/file_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/file/file_lib.o ${OBJECTDIR}/file/file_lib_nomain.o;\
	fi

${OBJECTDIR}/html2txt/html2txt_api_nomain.o: ${OBJECTDIR}/html2txt/html2txt_api.o html2txt/html2txt_api.c 
	${MKDIR} -p ${OBJECTDIR}/html2txt
	@NMOUTPUT=`${NM} ${OBJECTDIR}/html2txt/html2txt_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/html2txt/html2txt_api_nomain.o html2txt/html2txt_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/html2txt/html2txt_api.o ${OBJECTDIR}/html2txt/html2txt_api_nomain.o;\
	fi

${OBJECTDIR}/html2txt/html2txt_lib_nomain.o: ${OBJECTDIR}/html2txt/html2txt_lib.o html2txt/html2txt_lib.c 
	${MKDIR} -p ${OBJECTDIR}/html2txt
	@NMOUTPUT=`${NM} ${OBJECTDIR}/html2txt/html2txt_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/html2txt/html2txt_lib_nomain.o html2txt/html2txt_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/html2txt/html2txt_lib.o ${OBJECTDIR}/html2txt/html2txt_lib_nomain.o;\
	fi

${OBJECTDIR}/list/list_api_nomain.o: ${OBJECTDIR}/list/list_api.o list/list_api.c 
	${MKDIR} -p ${OBJECTDIR}/list
	@NMOUTPUT=`${NM} ${OBJECTDIR}/list/list_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/list/list_api_nomain.o list/list_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/list/list_api.o ${OBJECTDIR}/list/list_api_nomain.o;\
	fi

${OBJECTDIR}/list/list_lib_nomain.o: ${OBJECTDIR}/list/list_lib.o list/list_lib.c 
	${MKDIR} -p ${OBJECTDIR}/list
	@NMOUTPUT=`${NM} ${OBJECTDIR}/list/list_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/list/list_lib_nomain.o list/list_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/list/list_lib.o ${OBJECTDIR}/list/list_lib_nomain.o;\
	fi

${OBJECTDIR}/log/log_api_nomain.o: ${OBJECTDIR}/log/log_api.o log/log_api.c 
	${MKDIR} -p ${OBJECTDIR}/log
	@NMOUTPUT=`${NM} ${OBJECTDIR}/log/log_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log/log_api_nomain.o log/log_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/log/log_api.o ${OBJECTDIR}/log/log_api_nomain.o;\
	fi

${OBJECTDIR}/log/log_lib_nomain.o: ${OBJECTDIR}/log/log_lib.o log/log_lib.c 
	${MKDIR} -p ${OBJECTDIR}/log
	@NMOUTPUT=`${NM} ${OBJECTDIR}/log/log_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log/log_lib_nomain.o log/log_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/log/log_lib.o ${OBJECTDIR}/log/log_lib_nomain.o;\
	fi

${OBJECTDIR}/mem/mem_api_nomain.o: ${OBJECTDIR}/mem/mem_api.o mem/mem_api.c 
	${MKDIR} -p ${OBJECTDIR}/mem
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mem/mem_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mem/mem_api_nomain.o mem/mem_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/mem/mem_api.o ${OBJECTDIR}/mem/mem_api_nomain.o;\
	fi

${OBJECTDIR}/mem/mem_lib_nomain.o: ${OBJECTDIR}/mem/mem_lib.o mem/mem_lib.c 
	${MKDIR} -p ${OBJECTDIR}/mem
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mem/mem_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mem/mem_lib_nomain.o mem/mem_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/mem/mem_lib.o ${OBJECTDIR}/mem/mem_lib_nomain.o;\
	fi

${OBJECTDIR}/queue/queue_api_nomain.o: ${OBJECTDIR}/queue/queue_api.o queue/queue_api.c 
	${MKDIR} -p ${OBJECTDIR}/queue
	@NMOUTPUT=`${NM} ${OBJECTDIR}/queue/queue_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/queue/queue_api_nomain.o queue/queue_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/queue/queue_api.o ${OBJECTDIR}/queue/queue_api_nomain.o;\
	fi

${OBJECTDIR}/queue/queue_lib_nomain.o: ${OBJECTDIR}/queue/queue_lib.o queue/queue_lib.c 
	${MKDIR} -p ${OBJECTDIR}/queue
	@NMOUTPUT=`${NM} ${OBJECTDIR}/queue/queue_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/queue/queue_lib_nomain.o queue/queue_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/queue/queue_lib.o ${OBJECTDIR}/queue/queue_lib_nomain.o;\
	fi

${OBJECTDIR}/sha1/sha1_api_nomain.o: ${OBJECTDIR}/sha1/sha1_api.o sha1/sha1_api.c 
	${MKDIR} -p ${OBJECTDIR}/sha1
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sha1/sha1_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sha1/sha1_api_nomain.o sha1/sha1_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/sha1/sha1_api.o ${OBJECTDIR}/sha1/sha1_api_nomain.o;\
	fi

${OBJECTDIR}/sha1/sha1_lib_nomain.o: ${OBJECTDIR}/sha1/sha1_lib.o sha1/sha1_lib.c 
	${MKDIR} -p ${OBJECTDIR}/sha1
	@NMOUTPUT=`${NM} ${OBJECTDIR}/sha1/sha1_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sha1/sha1_lib_nomain.o sha1/sha1_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/sha1/sha1_lib.o ${OBJECTDIR}/sha1/sha1_lib_nomain.o;\
	fi

${OBJECTDIR}/store/store_api_nomain.o: ${OBJECTDIR}/store/store_api.o store/store_api.c 
	${MKDIR} -p ${OBJECTDIR}/store
	@NMOUTPUT=`${NM} ${OBJECTDIR}/store/store_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/store/store_api_nomain.o store/store_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/store/store_api.o ${OBJECTDIR}/store/store_api_nomain.o;\
	fi

${OBJECTDIR}/store/store_lib_nomain.o: ${OBJECTDIR}/store/store_lib.o store/store_lib.c 
	${MKDIR} -p ${OBJECTDIR}/store
	@NMOUTPUT=`${NM} ${OBJECTDIR}/store/store_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/store/store_lib_nomain.o store/store_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/store/store_lib.o ${OBJECTDIR}/store/store_lib_nomain.o;\
	fi

${OBJECTDIR}/tcpip/tcpip_api_nomain.o: ${OBJECTDIR}/tcpip/tcpip_api.o tcpip/tcpip_api.c 
	${MKDIR} -p ${OBJECTDIR}/tcpip
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tcpip/tcpip_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcpip/tcpip_api_nomain.o tcpip/tcpip_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tcpip/tcpip_api.o ${OBJECTDIR}/tcpip/tcpip_api_nomain.o;\
	fi

${OBJECTDIR}/tcpip/tcpip_lib_nomain.o: ${OBJECTDIR}/tcpip/tcpip_lib.o tcpip/tcpip_lib.c 
	${MKDIR} -p ${OBJECTDIR}/tcpip
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tcpip/tcpip_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tcpip/tcpip_lib_nomain.o tcpip/tcpip_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tcpip/tcpip_lib.o ${OBJECTDIR}/tcpip/tcpip_lib_nomain.o;\
	fi

${OBJECTDIR}/text/text_api_nomain.o: ${OBJECTDIR}/text/text_api.o text/text_api.c 
	${MKDIR} -p ${OBJECTDIR}/text
	@NMOUTPUT=`${NM} ${OBJECTDIR}/text/text_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/text/text_api_nomain.o text/text_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/text/text_api.o ${OBJECTDIR}/text/text_api_nomain.o;\
	fi

${OBJECTDIR}/text/text_lib_nomain.o: ${OBJECTDIR}/text/text_lib.o text/text_lib.c 
	${MKDIR} -p ${OBJECTDIR}/text
	@NMOUTPUT=`${NM} ${OBJECTDIR}/text/text_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/text/text_lib_nomain.o text/text_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/text/text_lib.o ${OBJECTDIR}/text/text_lib_nomain.o;\
	fi

${OBJECTDIR}/thread/thread_api_nomain.o: ${OBJECTDIR}/thread/thread_api.o thread/thread_api.c 
	${MKDIR} -p ${OBJECTDIR}/thread
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thread/thread_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thread/thread_api_nomain.o thread/thread_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/thread/thread_api.o ${OBJECTDIR}/thread/thread_api_nomain.o;\
	fi

${OBJECTDIR}/thread/thread_lib_nomain.o: ${OBJECTDIR}/thread/thread_lib.o thread/thread_lib.c 
	${MKDIR} -p ${OBJECTDIR}/thread
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thread/thread_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thread/thread_lib_nomain.o thread/thread_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/thread/thread_lib.o ${OBJECTDIR}/thread/thread_lib_nomain.o;\
	fi

${OBJECTDIR}/token/token_api_nomain.o: ${OBJECTDIR}/token/token_api.o token/token_api.c 
	${MKDIR} -p ${OBJECTDIR}/token
	@NMOUTPUT=`${NM} ${OBJECTDIR}/token/token_api.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/token/token_api_nomain.o token/token_api.c;\
	else  \
	    ${CP} ${OBJECTDIR}/token/token_api.o ${OBJECTDIR}/token/token_api_nomain.o;\
	fi

${OBJECTDIR}/token/token_lib_nomain.o: ${OBJECTDIR}/token/token_lib.o token/token_lib.c 
	${MKDIR} -p ${OBJECTDIR}/token
	@NMOUTPUT=`${NM} ${OBJECTDIR}/token/token_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -Iinclude -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/token/token_lib_nomain.o token/token_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/token/token_lib.o ${OBJECTDIR}/token/token_lib_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
