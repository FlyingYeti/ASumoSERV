#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Sources/Asservissement.c Sources/AsservissementVitesse.c Sources/Clock.c Sources/Init.c Sources/Interpreter.c Sources/Mouvement.c Sources/newmainXC16.c Sources/PID.c Sources/PWM.c Sources/UART.c Sources/PID_.c Sources/AsservissementPosition.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Sources/Asservissement.o ${OBJECTDIR}/Sources/AsservissementVitesse.o ${OBJECTDIR}/Sources/Clock.o ${OBJECTDIR}/Sources/Init.o ${OBJECTDIR}/Sources/Interpreter.o ${OBJECTDIR}/Sources/Mouvement.o ${OBJECTDIR}/Sources/newmainXC16.o ${OBJECTDIR}/Sources/PID.o ${OBJECTDIR}/Sources/PWM.o ${OBJECTDIR}/Sources/UART.o ${OBJECTDIR}/Sources/PID_.o ${OBJECTDIR}/Sources/AsservissementPosition.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Sources/Asservissement.o.d ${OBJECTDIR}/Sources/AsservissementVitesse.o.d ${OBJECTDIR}/Sources/Clock.o.d ${OBJECTDIR}/Sources/Init.o.d ${OBJECTDIR}/Sources/Interpreter.o.d ${OBJECTDIR}/Sources/Mouvement.o.d ${OBJECTDIR}/Sources/newmainXC16.o.d ${OBJECTDIR}/Sources/PID.o.d ${OBJECTDIR}/Sources/PWM.o.d ${OBJECTDIR}/Sources/UART.o.d ${OBJECTDIR}/Sources/PID_.o.d ${OBJECTDIR}/Sources/AsservissementPosition.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Sources/Asservissement.o ${OBJECTDIR}/Sources/AsservissementVitesse.o ${OBJECTDIR}/Sources/Clock.o ${OBJECTDIR}/Sources/Init.o ${OBJECTDIR}/Sources/Interpreter.o ${OBJECTDIR}/Sources/Mouvement.o ${OBJECTDIR}/Sources/newmainXC16.o ${OBJECTDIR}/Sources/PID.o ${OBJECTDIR}/Sources/PWM.o ${OBJECTDIR}/Sources/UART.o ${OBJECTDIR}/Sources/PID_.o ${OBJECTDIR}/Sources/AsservissementPosition.o

# Source Files
SOURCEFILES=Sources/Asservissement.c Sources/AsservissementVitesse.c Sources/Clock.c Sources/Init.c Sources/Interpreter.c Sources/Mouvement.c Sources/newmainXC16.c Sources/PID.c Sources/PWM.c Sources/UART.c Sources/PID_.c Sources/AsservissementPosition.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Sources/Asservissement.o: Sources/Asservissement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Asservissement.o.d 
	@${RM} ${OBJECTDIR}/Sources/Asservissement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Asservissement.c  -o ${OBJECTDIR}/Sources/Asservissement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Asservissement.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Asservissement.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/AsservissementVitesse.o: Sources/AsservissementVitesse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/AsservissementVitesse.o.d 
	@${RM} ${OBJECTDIR}/Sources/AsservissementVitesse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/AsservissementVitesse.c  -o ${OBJECTDIR}/Sources/AsservissementVitesse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/AsservissementVitesse.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/AsservissementVitesse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Clock.o: Sources/Clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Clock.o.d 
	@${RM} ${OBJECTDIR}/Sources/Clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Clock.c  -o ${OBJECTDIR}/Sources/Clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Init.o: Sources/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Init.o.d 
	@${RM} ${OBJECTDIR}/Sources/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Init.c  -o ${OBJECTDIR}/Sources/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Init.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Interpreter.o: Sources/Interpreter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Interpreter.o.d 
	@${RM} ${OBJECTDIR}/Sources/Interpreter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Interpreter.c  -o ${OBJECTDIR}/Sources/Interpreter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Interpreter.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Interpreter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Mouvement.o: Sources/Mouvement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Mouvement.o.d 
	@${RM} ${OBJECTDIR}/Sources/Mouvement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Mouvement.c  -o ${OBJECTDIR}/Sources/Mouvement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Mouvement.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Mouvement.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/newmainXC16.o: Sources/newmainXC16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/newmainXC16.o.d 
	@${RM} ${OBJECTDIR}/Sources/newmainXC16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/newmainXC16.c  -o ${OBJECTDIR}/Sources/newmainXC16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/newmainXC16.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/newmainXC16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/PID.o: Sources/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/PID.o.d 
	@${RM} ${OBJECTDIR}/Sources/PID.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/PID.c  -o ${OBJECTDIR}/Sources/PID.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/PID.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/PID.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/PWM.o: Sources/PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/PWM.o.d 
	@${RM} ${OBJECTDIR}/Sources/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/PWM.c  -o ${OBJECTDIR}/Sources/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/PWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/UART.o: Sources/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/UART.o.d 
	@${RM} ${OBJECTDIR}/Sources/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/UART.c  -o ${OBJECTDIR}/Sources/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/UART.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/PID_.o: Sources/PID_.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/PID_.o.d 
	@${RM} ${OBJECTDIR}/Sources/PID_.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/PID_.c  -o ${OBJECTDIR}/Sources/PID_.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/PID_.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/PID_.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/AsservissementPosition.o: Sources/AsservissementPosition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/AsservissementPosition.o.d 
	@${RM} ${OBJECTDIR}/Sources/AsservissementPosition.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/AsservissementPosition.c  -o ${OBJECTDIR}/Sources/AsservissementPosition.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/AsservissementPosition.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/AsservissementPosition.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Sources/Asservissement.o: Sources/Asservissement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Asservissement.o.d 
	@${RM} ${OBJECTDIR}/Sources/Asservissement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Asservissement.c  -o ${OBJECTDIR}/Sources/Asservissement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Asservissement.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Asservissement.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/AsservissementVitesse.o: Sources/AsservissementVitesse.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/AsservissementVitesse.o.d 
	@${RM} ${OBJECTDIR}/Sources/AsservissementVitesse.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/AsservissementVitesse.c  -o ${OBJECTDIR}/Sources/AsservissementVitesse.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/AsservissementVitesse.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/AsservissementVitesse.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Clock.o: Sources/Clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Clock.o.d 
	@${RM} ${OBJECTDIR}/Sources/Clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Clock.c  -o ${OBJECTDIR}/Sources/Clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Clock.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Init.o: Sources/Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Init.o.d 
	@${RM} ${OBJECTDIR}/Sources/Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Init.c  -o ${OBJECTDIR}/Sources/Init.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Init.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Init.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Interpreter.o: Sources/Interpreter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Interpreter.o.d 
	@${RM} ${OBJECTDIR}/Sources/Interpreter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Interpreter.c  -o ${OBJECTDIR}/Sources/Interpreter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Interpreter.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Interpreter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/Mouvement.o: Sources/Mouvement.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/Mouvement.o.d 
	@${RM} ${OBJECTDIR}/Sources/Mouvement.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/Mouvement.c  -o ${OBJECTDIR}/Sources/Mouvement.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/Mouvement.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/Mouvement.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/newmainXC16.o: Sources/newmainXC16.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/newmainXC16.o.d 
	@${RM} ${OBJECTDIR}/Sources/newmainXC16.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/newmainXC16.c  -o ${OBJECTDIR}/Sources/newmainXC16.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/newmainXC16.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/newmainXC16.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/PID.o: Sources/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/PID.o.d 
	@${RM} ${OBJECTDIR}/Sources/PID.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/PID.c  -o ${OBJECTDIR}/Sources/PID.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/PID.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/PID.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/PWM.o: Sources/PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/PWM.o.d 
	@${RM} ${OBJECTDIR}/Sources/PWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/PWM.c  -o ${OBJECTDIR}/Sources/PWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/PWM.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/PWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/UART.o: Sources/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/UART.o.d 
	@${RM} ${OBJECTDIR}/Sources/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/UART.c  -o ${OBJECTDIR}/Sources/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/UART.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/PID_.o: Sources/PID_.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/PID_.o.d 
	@${RM} ${OBJECTDIR}/Sources/PID_.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/PID_.c  -o ${OBJECTDIR}/Sources/PID_.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/PID_.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/PID_.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Sources/AsservissementPosition.o: Sources/AsservissementPosition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/Sources 
	@${RM} ${OBJECTDIR}/Sources/AsservissementPosition.o.d 
	@${RM} ${OBJECTDIR}/Sources/AsservissementPosition.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Sources/AsservissementPosition.c  -o ${OBJECTDIR}/Sources/AsservissementPosition.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Sources/AsservissementPosition.o.d"        -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=on
	@${FIXDEPS} "${OBJECTDIR}/Sources/AsservissementPosition.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ASumoSERV.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
