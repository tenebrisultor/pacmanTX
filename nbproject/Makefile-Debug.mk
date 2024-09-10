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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=
CXX=
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/mailboxserver.o \
	${OBJECTDIR}/tsktool.o \
	${OBJECTDIR}/graph.o \
	${OBJECTDIR}/locks.o \
	${OBJECTDIR}/mailbox.o \
	${OBJECTDIR}/worm.o \
	${OBJECTDIR}/gameobj.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/clisrv.o \
	${OBJECTDIR}/collman.o \
	${OBJECTDIR}/task.o \
	${OBJECTDIR}/pacman.o \
	${OBJECTDIR}/adt.o \
	${OBJECTDIR}/memseg.o \
	${OBJECTDIR}/shdadt.o \
	${OBJECTDIR}/gamefield.o \
	${OBJECTDIR}/dummy.o \
	${OBJECTDIR}/chnls.o \
	${OBJECTDIR}/myipc.o \
	${OBJECTDIR}/shdmry.o \
	${OBJECTDIR}/ghost.o

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
LDLIBSOPTIONS=-lpthread -lcurses

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/pacmantx

dist/Debug/GNU-Linux-x86/pacmantx: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pacmantx ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/mailboxserver.o: nbproject/Makefile-${CND_CONF}.mk mailboxserver.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/mailboxserver.o mailboxserver.c

${OBJECTDIR}/tsktool.o: nbproject/Makefile-${CND_CONF}.mk tsktool.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/tsktool.o tsktool.c

${OBJECTDIR}/graph.o: nbproject/Makefile-${CND_CONF}.mk graph.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/graph.o graph.c

${OBJECTDIR}/locks.o: nbproject/Makefile-${CND_CONF}.mk locks.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/locks.o locks.c

${OBJECTDIR}/mailbox.o: nbproject/Makefile-${CND_CONF}.mk mailbox.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/mailbox.o mailbox.c

${OBJECTDIR}/worm.o: nbproject/Makefile-${CND_CONF}.mk worm.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/worm.o worm.c

${OBJECTDIR}/gameobj.o: nbproject/Makefile-${CND_CONF}.mk gameobj.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/gameobj.o gameobj.c

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/clisrv.o: nbproject/Makefile-${CND_CONF}.mk clisrv.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/clisrv.o clisrv.c

${OBJECTDIR}/collman.o: nbproject/Makefile-${CND_CONF}.mk collman.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/collman.o collman.c

${OBJECTDIR}/task.o: nbproject/Makefile-${CND_CONF}.mk task.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/task.o task.c

${OBJECTDIR}/pacman.o: nbproject/Makefile-${CND_CONF}.mk pacman.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/pacman.o pacman.c

${OBJECTDIR}/adt.o: nbproject/Makefile-${CND_CONF}.mk adt.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/adt.o adt.c

${OBJECTDIR}/memseg.o: nbproject/Makefile-${CND_CONF}.mk memseg.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/memseg.o memseg.c

${OBJECTDIR}/shdadt.o: nbproject/Makefile-${CND_CONF}.mk shdadt.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/shdadt.o shdadt.c

${OBJECTDIR}/gamefield.o: nbproject/Makefile-${CND_CONF}.mk gamefield.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/gamefield.o gamefield.c

${OBJECTDIR}/dummy.o: nbproject/Makefile-${CND_CONF}.mk dummy.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/dummy.o dummy.c

${OBJECTDIR}/chnls.o: nbproject/Makefile-${CND_CONF}.mk chnls.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/chnls.o chnls.c

${OBJECTDIR}/myipc.o: nbproject/Makefile-${CND_CONF}.mk myipc.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/myipc.o myipc.c

${OBJECTDIR}/shdmry.o: nbproject/Makefile-${CND_CONF}.mk shdmry.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/shdmry.o shdmry.c

${OBJECTDIR}/ghost.o: nbproject/Makefile-${CND_CONF}.mk ghost.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/ghost.o ghost.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/pacmantx

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
