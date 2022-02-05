# plugin's source file in current directory.
# for example SRCFILE = plugin.cpp
SRCFILE = qqbot.cpp

# Valve sourceSDK directory.
# for example SDKDIR = /home/user/source-sdk-2013/mp/src
SDKDIR = /home/cialloo/repo/sourceSDK/mp/src

# a directory to store plugin
# for example COMPILEDPATH = compiled
COMPILEDPATH = compiled

# steam runtime directory
# for example STEAMRUNTIMEDIR = /valve/steam-runtime
STEAMRUNTIMEDIR = /valve/steam-runtime



###		DO NOT EDIT BELOW!!!	###

PROJECTDIR = $(shell pwd)

SDKLIBS = $(SDKDIR)/lib/public/linux32

SymbolVisibility = -fvisibility=hidden

ARCH_FLAGS = \
-m32 \
-march=pentium4 \
-mtune=core2 \
-msse2 \
-mfpmath=sse

DEFINES = \
-DVPC \
-DRAD_TELEMETRY_DISABLED \
-DNDEBUG \
-DGNUC \
-DPOSIX \
-DCOMPILER_GCC \
-D_DLL_EXT=.so \
-D_LINUX \
-DLINUX \
-DPOSIX \
-D_POSIX \
-DDLLNAME=serverplugin_empty \
-DBINK_VIDEO \
-DGL_GLEXT_PROTOTYPES \
-DDX_TO_GL_ABSTRACTION \
-DUSE_SDL \
-DDEV_BUILD \
-DFRAME_POINTER_OMISSION_DISABLED \
-Dserverplugin_emptyONLY \
-D_MBCS \
-D_EXTERNAL_DLL_EXT=.so \
-DVPCGAMECAPS=HL2MP \
-DPROJECTDIR=$(PROJECTDIR) \
-D_DLL_EXT=.so \
-DSOURCE1=1 \
-DVPCGAME=hl2mp \
-D_LINUX=1 \
-D_POSIX=1 \
-DLINUX=1 \
-DPOSIX=1  \
-DVPROF_LEVEL=1 \
-DGNUC \
-DNO_HOOK_MALLOC \
-DNO_MALLOC_OVERRIDE

HEADFILES = \
-I$(SDKDIR)/common \
-I$(SDKDIR)/public \
-I$(SDKDIR)/public/tier0 \
-I$(SDKDIR)/public/tier1 \
-I$(SDKDIR)/thirdparty/SDL2 \
-I$(SDKDIR)/game/server \
-I$(SDKDIR)/game/shared

OptimizerLevel = \
-gdwarf-4 \
-g2 \
-O2 \
-fno-strict-aliasing \
-ffast-math \
-fno-omit-frame-pointer \
-ftree-vectorize \
-fpredictive-commoning \
-funswitch-loops

# CXX
CXX = \
$(SDKDIR)/devtools/bin/linux/ccache \
$(STEAMRUNTIMEDIR)/bin/g++

WARN_CXXFLAGS = \
-Wall \
-Wno-invalid-offsetof \
-Wno-multichar \
-Wno-overloaded-virtual \
-Wno-write-strings \
-Wno-unused-variable \
-Wno-unused-but-set-variable \
-Wno-unused-function \
-Wno-unknown-pragmas \
-Wno-unused-parameter \
-Wno-unused-value \
-Wno-missing-field-initializers \
-Wno-sign-compare \
-Wno-reorder \
-Wno-invalid-offsetof \
-Wno-float-equal \
-Werror=return-type \
-fdiagnostics-show-option \
-Wformat \
-Wformat-security \
-fdiagnostics-show-option \
-Wformat \
-Wformat-security

WARN_CFLAGS = \
-Wall \
-Wno-invalid-offsetof \
-Wno-multichar \
-Wno-overloaded-virtual \
-Wno-write-strings \
-Wno-unused-variable \
-Wno-unused-but-set-variable \
-Wno-unused-function \
-Wno-unknown-pragmas \
-Wno-unused-parameter \
-Wno-unused-value \
-Wno-missing-field-initializers \
-Wno-sign-compare \
-Wno-reorder \
-Wno-invalid-offsetof \
-Wno-float-equal \
-Werror=return-type \
-fdiagnostics-show-option \
-Wformat \
-Wformat-security

# below are precompile flags
CXXFLAGS = \
$(SymbolVisibility) \
$(ARCH_FLAGS) \
$(WARN_CXXFLAGS) \
$(DEFINES) \
$(HEADFILES) \
$(OptimizerLevel) \
$(BASE_CFLAGS)

BASE_CFLAGS = \
-pipe  \
-Usprintf \
-Ustrncpy \
-UPROTECTED_THINGS_ENABLE \
-std=gnu++0x \
-fpermissive  \
-MMD \
-MP \
-MF \
$(COMPILEDPATH)/$(@:.o=.P)

# below are linking flags 
CC = \
$(SDKDIR)/devtools/bin/linux/ccache \
$(STEAMRUNTIMEDIR)/bin/gcc

SHLIBLDFLAGS = -shared

LINK_MAP_FLAGS = -Wl,-Map,$(COMPILEDPATH)/$(SRCFILE:.cpp=.map)

LDFLAGS = \
-Wl,--build-id \
-m32 \
-Wl,--no-undefined

_WRAP = \
-Xlinker \
--wrap=fopen \
-Xlinker \
--wrap=freopen \
-Xlinker \
--wrap=open    \
-Xlinker \
--wrap=creat    \
-Xlinker \
--wrap=access  \
-Xlinker \
--wrap=__xstat \
-Xlinker \
--wrap=stat  \
-Xlinker \
--wrap=lstat   \
-Xlinker \
--wrap=fopen64 \
-Xlinker \
--wrap=open64   \
-Xlinker \
--wrap=opendir \
-Xlinker \
--wrap=__lxstat \
-Xlinker \
--wrap=chmod \
-Xlinker \
--wrap=chown   \
-Xlinker \
--wrap=lchown  \
-Xlinker \
--wrap=symlink  \
-Xlinker \
--wrap=link    \
-Xlinker \
--wrap=__lxstat64 \
-Xlinker \
--wrap=mknod \
-Xlinker \
--wrap=utimes  \
-Xlinker \
--wrap=unlink  \
-Xlinker \
--wrap=rename   \
-Xlinker \
--wrap=utime   \
-Xlinker \
--wrap=__xstat64 \
-Xlinker \
--wrap=mount \
-Xlinker \
--wrap=mkfifo  \
-Xlinker \
--wrap=mkdir   \
-Xlinker \
--wrap=rmdir    \
-Xlinker \
--wrap=scandir \
-Xlinker \
--wrap=realpath

LIB_START_SHLIB = \
-static-libgcc \
-Wl,--start-group

LIBFILES = \
$(COMPILEDPATH)/$(SRCFILE:.cpp=.o) \
$(SDKLIBS)/tier1.a \
$(SDKLIBS)/mathlib.a \
$(SDKLIBS)/tier2.a \
-L$(SDKLIBS) \
-ltier0 \
-L$(SDKLIBS) \
-lvstdlib   \
-Wl,--end-group \
-lm \
-ldl \
$(STEAMRUNTIMEDIR)/amd64/i686-unknown-linux-gnu/bin/../lib/gcc/i686-unknown-linux-gnu/4.6.3/../../../../i686-unknown-linux-gnu/lib/libstdc++.so \
-lpthread \
-l:ld-linux.so.2 \
-Wl,--version-script=$(SDKDIR)/devtools/version_script.linux.txt;

CFLAGS = \
$(LINK_MAP_FLAGS) \
$(SymbolVisibility) \
$(ARCH_FLAGS) \
$(SHLIBLDFLAGS) \
$(WARN_CFLAGS) \
$(DEFINES) \
$(HEADFILES) \
$(OptimizerLevel) \
$(LDFLAGS) \
$(_WRAP) \
$(LIB_START_SHLIB) \
$(LIBFILES) \


$(SRCFILE:.cpp=.so) : $(SRCFILE:.cpp=.o) $(SRCFILE:.cpp=.o) $(SRCFILE:.cpp=.map)
	@echo compile complete.

$(SRCFILE:.cpp=.o) : $(SRCFILE)
	@echo ---- start to compile the plugin $@ ----
	@echo compiling $@
	@mkdir -p $(COMPILEDPATH)
	@$(CXX) $(CXXFLAGS) -o ./$(COMPILEDPATH)/$@ -c $<
	@echo precompile finished.

$(SRCFILE:.cpp=.map) : $(SRCFILE:.cpp=.o)
	@echo drawing $@
	@$(CC) -o ./$(COMPILEDPATH)/$(SRCFILE:.cpp=.so) $(CFLAGS) 


.PHONY: clean

clean :
	@rm -rf $(COMPILEDPATH)