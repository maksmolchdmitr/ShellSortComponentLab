# include directories
INC = \
-I ..\..\..\HeaderFiles \
-I ..\..\..\SharedFiles \
-I ..\..\..\..\Eco.Core1\SharedFiles \
-I ..\..\..\..\Eco.InterfaceBus1\SharedFiles \
-I ..\..\..\..\Eco.MemoryManager1\SharedFiles

# source files.
SRC = \
..\..\..\SourceFiles\CEcoCalculatorE.c \
..\..\..\SourceFiles\CEcoCalculatorEFactory.c

OBJ = $(SRC:.c=.o)

OUT = lib872FEF1DE3314B87AD44D1E7C232C2F0.a
OUT_DIR = ..\..\..\BuildFiles\BCM283x\arm64-v8a\StaticRelease

 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -Wall -O3 -Wno-missing-braces -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -DECO_LIB -DECO_BCM283X -DUGUID_UTILITY
 
# compiler
ARMGNU  = $(ECO_TOOLCHAIN)/gcc-linaro-7.5.0/bin/
CCC = $(ARMGNU)aarch64-elf-gcc
 
# library paths
LIBS = -lc -lm -lgcc
 
# compile flags
LDFLAGS = -g

.SUFFIXES: .c

 all: $(OUT)

.c.o:
	$(CCC) $(INC) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	$(ARMGNU)aarch64-elf-ar -rcs $(OUT_DIR)\$(OUT) $(OBJ)
 

clean:
	del -f $(OBJ) $(OUT_DIR)\$(OUT)