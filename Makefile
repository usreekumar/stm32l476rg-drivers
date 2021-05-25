# Name of the binariy.
PROJ_NAME = stm32l476rg-drivers

# Specifying the header file directories
INCS_DIR  = ./App/Inc
INCS_DIR += ./Drivers/Inc

# Specifying the src file directories
SRCS_DIR  = ./App/Src
SRCS_DIR += ./Drivers/Src

# Specifying the build file directories
BUILD_DIR = ./Builds

#Adding -I flags before the include folders to let the compiler know the paths to search 
INCLUDES := $(addprefix -I, $(INCS_DIR))

# Getting all the files with .c extenstion in the source directories and addding the startup file into it.
SRCS     = $(shell find $(SRCS_DIR) -name *.c)
SRCS    += ./App/Startup/startup_stm32l476xx_gcc.s

# -D is a preprocessor flag passed to GCC to define something before compilation. 
#  SE_STDPERIPH_DRIVER is needed to work with the STM library
DEFS    = -DUSE_STDPERIPH_DRIVER

# Tools needed
BIN_DIR = /home/umamaheswaran/Embedded/tools/gcc-arm-none-eabi-10-2020-q4-major/bin

# The GNU Compiler Collection is an optimizing compiler produced by the GNU Project 
# supporting various programming languages, 
CC 		= $(BIN_DIR)/arm-none-eabi-gcc
# The GNU objcopy utility copies the contents of an object file to another. 
OBJCOPY = $(BIN_DIR)/arm-none-eabi-objcopy
# GDB
GDB     = $(BIN_DIR)/arm-none-eabi-gdb


#Path to st-flash executable
STFLASH = /home/umamaheswaran/Embedded/tools/stlink/bin/st-flash

# Compiler flags

CFLAGS  = -ggdb	 # Produces debugging information intended for gdb
CFLAGS += -O0 	 # -O0 => Optimizations are disbled

#  Ref   		 : https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
#
# -Wall  		 : This enables all the warnings about constructions that some users consider 
#		   	  	   questionable, and that are easy to avoid
# -Wextra		 : This enables some extra warning flags that are not enabled by -Wall
# -Warray-bounds : It warns about subscripts to arrays that are always out of bounds.
CFLAGS += -Wall -Wextra -Warray-bounds 

#  Ref		  	    : https://gcc.gnu.org/onlinedocs/gcc-4.3.2/gcc/ARM-Options.html
# -mlittle-endian   : Generate code for a processor running in little-endian mode. 
# -mthumb           : Generate code for the Thumb instruction set. The default  
#					  is to use the 32-bit ARM instruction set.
# -mcpu			    : This specifies the name of the target ARM processor. GCC uses this name 
#					  to determine what kind of instructions it can emit when generating assembly code.
# -mthumb-interwork : Generate code which supports calling between the ARM and Thumb instruction sets.
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork

# Ref 			    : https://embeddedartistry.com/blog/2017/10/11/demystifying-arm-floating-point-compiler-options/
# -mfloat-abi=hard  : The -mfloat-abi=<name> option is used to select which ARM ABI is used.
#					  The hard option enables full hardware floating-point support.
# 					  When using the hard or softfp float-abi, you should specify the FPU type 
#					  using the -mfpu compiler flag.
# -mfpu=fpv4-sp-d16 : This flag specifies what floating-point hardware (or emulation) is 
#					  available on your target architecture. Cortex M4F ahs fpv4-sp-d16 
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

# Linker Related stuff. Tells which linker file to use.
# non-semihosting/retarget
# If you are using retarget, linking like:
# $ arm-none-eabi-gcc --specs=nosys.specs $(OTHER_LINK_OPTIONS)
# Ref : https://stackoverflow.com/questions/19419782/exit-c-text0x18-undefined-reference-to-exit-when-using-arm-none-eabi-gcc
LFLAGS = --specs=nosys.specs -TSTM32L476RGTX_FLASH.ld

# Compilations process

# A phony target is one that is not really the name of a file; rather it is just a 
# name for a recipe to be executed when you make an explicit request. 

.PHONY: $(PROJ_NAME)
$(PROJ_NAME): $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	@$(CC) $(INCLUDES) $(DEFS) $(CFLAGS) $(LFLAGS) $^ -o $(BUILD_DIR)/$@
	@$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJ_NAME).elf   $(BUILD_DIR)/$(PROJ_NAME).hex
	@$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).bin

flash: 
	$(STFLASH) write $(BUILD_DIR)/$(PROJ_NAME).bin 0x8000000

# Open OCD config
OPENOCD_CFG = /home/umamaheswaran/Embedded/tools/openocd-0.11.0/tcl/board/st_nucleo_l4.cfg
openocd_launch:
	openocd -f $(OPENOCD_CFG)

# Use arm-none-eabi-gdb to debug
debug:
	$(GDB) -q $(BUILD_DIR)/$(PROJ_NAME).elf

# clean will remove all the files in the BUILD_DIR
clean:
	rm -f $(BUILD_DIR)/*