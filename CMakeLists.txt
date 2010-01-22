PROJECT(wxmapconv)

#set minimum cmake version
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_COLOR_MAKEFILE ON)

# Add Definitions, Compiler-Switches, etc.: -Wall -O2 -g3 ...
# MSVC compiler (cl.exe) does not accept the same switches as gcc, although preprocessor definitions in the -D form will work for both
IF(NOT MSVC)
	ADD_DEFINITIONS(-Wall -Wno-strict-aliasing -Wextra)
ENDIF(NOT MSVC)
IF(WIN32)
	ADD_DEFINITIONS( -DWXUSINGDLL -D__WXMSW__ -D_WIN32_WINNT=0x0501)
ENDIF(WIN32)
IF(MSVC)
	ADD_DEFINITIONS(-D_RC_MSVC)
ENDIF(MSVC)

#----------------------------------------------------------------------------------------------------
# General Settings
#----------------------------------------------------------------------------------------------------
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true )
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".lib" ".a")

SET( OPTION_TRANSLATION_SUPPORT
	0 CACHE BOOL
	"Enables translation support to the programs and adds facilities for helping translators (requires GNU Gettext)" )

#----------------------------------------------------------------------------------------------------
# Load needed Modules
#----------------------------------------------------------------------------------------------------
EXECUTE_PROCESS(COMMAND ${wxmapconv_SOURCE_DIR}/tools/get-revision.sh
        OUTPUT_VARIABLE wxmapconv_GIT_REV
        ERROR_VARIABLE GIT_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
		)

INCLUDE(cmake/package_config.cmake)
INCLUDE(cmake/sources.list)
# PKG-Config
#----------------------------------------------------------------------------------------------------
# wxWidgets lib dependency check
#----------------------------------------------------------------------------------------------------

# Here you can define, what Libraries of wxWidgets you need for your Application. You can figure out what Libraries you need here:
# http://www.wxwidgets.org/manuals/2.8/wx_librarieslist.html
IF(NOT CMAKE_CROSSCOMPILING)
	SET(wxWidgets_USE_LIBS base core adv aui )

	# We need the Find package for wxWidgets to work
	FIND_PACKAGE(wxWidgets REQUIRED base core adv aui )

	# Did we find wxWidgets ? This condition will fail for as long as the internal Vars do not point to the proper wxWidgets Configuration.
	IF(wxWidgets_FOUND)
		# Include wxWidgets macros
		INCLUDE(${wxWidgets_USE_FILE})
		IF(MSVC)
			INCLUDE_DIRECTORIES( ${wxWidgets_ROOT_DIR}/include/msvc )
		ENDIF(MSVC)
		IF(MINGW)
			SET(wxWidgets_RC_DIR ${wxWidgets_ROOT_DIR}/include)
		ENDIF(MINGW)
		INCLUDE_DIRECTORIES( ${wxWidgets_INCLUDE_DIRS} )
	ELSE(wxWidgets_FOUND)
		# For Convenience. If we cannot continue, inform the User.
		MESSAGE( FATAL_ERROR "wxWidgets library not found! Please install the package to continue")
	ENDIF(wxWidgets_FOUND)
ELSE (NOT CMAKE_CROSSCOMPILING)
    INCLUDE_DIRECTORIES( ${wxWidgets_INCLUDE_DIRS} )
    link_directories( ${wxWidgets_LIB_DIR} )
ENDIF(NOT CMAKE_CROSSCOMPILING)


# If we build for windows Systems, we also include the Resource-File containing the Manifest, Icon and other Resources.
IF(WIN32)
	IF(MINGW OR CMAKE_CROSSCOMPILING)
		FIND_PROGRAM(WINDRES NAMES i586-pc-mingw32-windres windres i686-mingw32-windres DOC "path to mingw's windres executable")
		ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/icon.o COMMAND ${WINDRES} -I${wxmapconv_SOURCE_DIR}/src -I${wxWidgets_RC_DIR} -i${wxmapconv_SOURCE_DIR}/src/resource.rc -o ${CMAKE_CURRENT_BINARY_DIR}/icon.o)
		SET(wxmapconv_RC_FILE ${CMAKE_CURRENT_BINARY_DIR}/icon.o )
	ENDIF(MINGW OR CMAKE_CROSSCOMPILING)

	SET(wxmapconvSrc ${wxmapconvSrc} src/resource.rc)
ENDIF(WIN32)

#----------------------------------------------------------------------------------------------------
# L10n support
#----------------------------------------------------------------------------------------------------
if( OPTION_TRANSLATION_SUPPORT )
	include ( ${CMAKE_SOURCE_DIR}/po/CMakeLists.txt )
endif( OPTION_TRANSLATION_SUPPORT )
ADD_DEFINITIONS( -DLOCALE_INSTALL_DIR="${LOCALE_INSTALL_DIR}" )

#----------------------------------------------------------------------------------------------------
# Build target defintions
#----------------------------------------------------------------------------------------------------

# Here we define the executable wxmapconv ( or on Windows wxmapconv.exe )

#auto-remove whitespaces before/after lib paths
cmake_policy(SET CMP0004 OLD)
#ignore warnings about macosx app bundle output dir
cmake_policy(SET CMP0006 OLD)

ADD_EXECUTABLE(wxmapconv WIN32 MACOSX_BUNDLE ${wxmapconvSrc} ${wxmapconv_RC_FILE})

# Here the wxWidgets Libraries are added. These are set for us by the FIND Script. If you need other Libraries, you can add them here as well.
TARGET_LINK_LIBRARIES(wxmapconv ${wxWidgets_LIBRARIES} )

IF (WIN32)
    install(TARGETS wxmapconv RUNTIME DESTINATION .)
    install(FILES AUTHORS COPYING README THANKS  DESTINATION .)
	install(DIRECTORY ${CMAKE_INSTALL_PREFIX}/locale DESTINATION .)
ELSE (WIN32)
    install(TARGETS wxmapconv RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
    install(FILES AUTHORS COPYING README THANKS DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/wxmapconv )
    install(FILES src/images/wxmapconv.svg DESTINATION
	    ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps)
    install(FILES src/wxmapconv.desktop DESTINATION
	    ${CMAKE_INSTALL_PREFIX}/share/applications)
ENDIF (WIN32)

