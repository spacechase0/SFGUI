cmake_minimum_required( VERSION 2.8 )

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE )
endif()

project( SFGUI )

### USER INPUT ###

set( BUILD_SHARED_LIBS true CACHE BOOL "Build dynamic library." )
set( BUILD_EXAMPLES true CACHE BOOL "Build SFGUI examples." )
set( SFML_STATIC_LIBRARIES false CACHE BOOL "Was SFML built as a static library?" )

if( SFML_STATIC_LIBRARIES AND BUILD_SHARED_LIBS )
	message( FATAL_ERROR "If you link to SFML statically you MUST link to SFGUI statically too." )
endif()

if( MSVC )
	set( STATIC_STD_LIBS false CACHE BOOL "True to link the runtime library statically, false to link them dynamically." )
endif()

find_package( OpenGL REQUIRED )
find_package( SFML 2.0 QUIET COMPONENTS GRAPHICS WINDOW SYSTEM )

# FindSFML was not run.
if( NOT DEFINED FIND_SFML_LIB_SUFFIX )
	set( CMAKE_MODULE_PATH "" CACHE PATH "SFML root directory" )
	message( FATAL_ERROR "CMake couldn't find FindSFML.cmake. Did you remember to install SFML?\nOptionally, you can set the CMAKE_MODULE_PATH entry to the directory containing FindSFML.cmake.\nFindSFML.cmake will be searched for in there." )
endif()

# FindSFML couldn't find SFML.
if( NOT SFML_FOUND )
	set( SFMLDIR "" CACHE PATH "SFML root directory" )
	message( FATAL_ERROR "CMake couldn't find SFML. Set the SFMLDIR entry to SFML's root directory (containing \"include\" and \"lib\" directories)." )
endif()

if( SFML_STATIC_LIBRARIES )
	# Even though FindSFML sets -DSFML_STATIC itself, better safe than sorry.
	add_definitions( -DSFML_STATIC )
endif()

# Set some useful compile flags.
if( CMAKE_COMPILER_IS_GNUCXX )
	if( NOT CMAKE_CXX_FLAGS )
		set( CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wno-long-long -pedantic" CACHE STRING "C++ compiler flags" FORCE )
		set( CMAKE_C_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wno-long-long -pedantic" CACHE STRING "C compiler flags" FORCE )
	endif()

	if( NOT CMAKE_CXX_FLAGS_DEBUG )
		set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "C++ compiler flags (debug)" FORCE )
		set( CMAKE_C_FLAGS_DEBUG "-g -O0" CACHE STRING "C++ compiler flags (debug)" FORCE )
	endif()
endif()

# Make windows happy.
if( WIN32 )
	set( BIN_EXTENSION ".exe" )
	set( SHARE_TARGET_DIR . )
	add_definitions( -DWIN32 )
else()
	set( SHARE_TARGET_DIR share/SFGUI )
endif()

set( LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib" )

set( SRC_DIR "${PROJECT_SOURCE_DIR}/src/" )
set( INC_DIR "${PROJECT_SOURCE_DIR}/include/" )

set(
	SOURCES
	${INC_DIR}/SFGUI/Adjustment.hpp
	${INC_DIR}/SFGUI/Alignment.hpp
	${INC_DIR}/SFGUI/Bin.hpp
	${INC_DIR}/SFGUI/Box.hpp
	${INC_DIR}/SFGUI/Button.hpp
	${INC_DIR}/SFGUI/CheckButton.hpp
	${INC_DIR}/SFGUI/ComboBox.hpp
	${INC_DIR}/SFGUI/Config.hpp
	${INC_DIR}/SFGUI/Container.hpp
	${INC_DIR}/SFGUI/Context.hpp
	${INC_DIR}/SFGUI/Desktop.hpp
	${INC_DIR}/SFGUI/Desktop.inl
	${INC_DIR}/SFGUI/Engine.hpp
	${INC_DIR}/SFGUI/Engine.inl
	${INC_DIR}/SFGUI/Engines/BREW.hpp
	${INC_DIR}/SFGUI/Entry.hpp
	${INC_DIR}/SFGUI/FastDelegate.hpp
	${INC_DIR}/SFGUI/FileResourceLoader.hpp
	${INC_DIR}/SFGUI/Fixed.hpp
	${INC_DIR}/SFGUI/Frame.hpp
	${INC_DIR}/SFGUI/Image.hpp
	${INC_DIR}/SFGUI/Label.hpp
	${INC_DIR}/SFGUI/Misc.hpp
	${INC_DIR}/SFGUI/NonCopyable.hpp
	${INC_DIR}/SFGUI/Notebook.hpp
	${INC_DIR}/SFGUI/Object.hpp
	${INC_DIR}/SFGUI/Parsers/ThemeParser/Grammar.hpp
	${INC_DIR}/SFGUI/Parsers/ThemeParser/Parse.hpp
	${INC_DIR}/SFGUI/Primitive.hpp
	${INC_DIR}/SFGUI/ProgressBar.hpp
	${INC_DIR}/SFGUI/Range.hpp
	${INC_DIR}/SFGUI/Renderer.hpp
	${INC_DIR}/SFGUI/RendererViewport.hpp
	${INC_DIR}/SFGUI/RenderQueue.hpp
	${INC_DIR}/SFGUI/ResourceLoader.hpp
	${INC_DIR}/SFGUI/ResourceManager.hpp
	${INC_DIR}/SFGUI/ResourceManager.inl
	${INC_DIR}/SFGUI/Scale.hpp
	${INC_DIR}/SFGUI/Scrollbar.hpp
	${INC_DIR}/SFGUI/ScrolledWindow.hpp
	${INC_DIR}/SFGUI/Selector.hpp
	${INC_DIR}/SFGUI/Separator.hpp
	${INC_DIR}/SFGUI/SFGUI.hpp
	${INC_DIR}/SFGUI/SharedPtr.hpp
	${INC_DIR}/SFGUI/SharedPtr.inl
	${INC_DIR}/SFGUI/Signal.hpp
	${INC_DIR}/SFGUI/Signal.inl
	${INC_DIR}/SFGUI/Spinner.hpp
	${INC_DIR}/SFGUI/Table.hpp
	${INC_DIR}/SFGUI/TableCell.hpp
	${INC_DIR}/SFGUI/TableOptions.hpp
	${INC_DIR}/SFGUI/ToggleButton.hpp
	${INC_DIR}/SFGUI/Viewport.hpp
	${INC_DIR}/SFGUI/Widget.hpp
	${INC_DIR}/SFGUI/Window.hpp
	${SRC_DIR}/SFGUI/Adjustment.cpp
	${SRC_DIR}/SFGUI/Alignment.cpp
	${SRC_DIR}/SFGUI/Bin.cpp
	${SRC_DIR}/SFGUI/Box.cpp
	${SRC_DIR}/SFGUI/Button.cpp
	${SRC_DIR}/SFGUI/CheckButton.cpp
	${SRC_DIR}/SFGUI/ComboBox.cpp
	${SRC_DIR}/SFGUI/Container.cpp
	${SRC_DIR}/SFGUI/Context.cpp
	${SRC_DIR}/SFGUI/Desktop.cpp
	${SRC_DIR}/SFGUI/Engine.cpp
	${SRC_DIR}/SFGUI/Engines/BREW.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Button.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/CheckButton.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/ComboBox.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Entry.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Frame.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Image.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Label.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Notebook.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/ProgressBar.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Scale.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Scrollbar.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/ScrolledWindow.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Separator.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Spinner.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/ToggleButton.cpp
	${SRC_DIR}/SFGUI/Engines/BREW/Window.cpp
	${SRC_DIR}/SFGUI/Entry.cpp
	${SRC_DIR}/SFGUI/FileResourceLoader.cpp
	${SRC_DIR}/SFGUI/Fixed.cpp
	${SRC_DIR}/SFGUI/Frame.cpp
	${SRC_DIR}/SFGUI/Image.cpp
	${SRC_DIR}/SFGUI/Label.cpp
	${SRC_DIR}/SFGUI/Misc.cpp
	${SRC_DIR}/SFGUI/NonCopyable.cpp
	${SRC_DIR}/SFGUI/Notebook.cpp
	${SRC_DIR}/SFGUI/Object.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/Grammar.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/GrammarPredicates.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/GrammarSelector.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/GrammarSimpleSelector.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/GrammarStatement.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/GrammarToken.cpp
	${SRC_DIR}/SFGUI/Parsers/ThemeParser/Parse.cpp
	${SRC_DIR}/SFGUI/Primitive.cpp
	${SRC_DIR}/SFGUI/ProgressBar.cpp
	${SRC_DIR}/SFGUI/Range.cpp
	${SRC_DIR}/SFGUI/Renderer.cpp
	${SRC_DIR}/SFGUI/RendererViewport.cpp
	${SRC_DIR}/SFGUI/RenderQueue.cpp
	${SRC_DIR}/SFGUI/ResourceLoader.cpp
	${SRC_DIR}/SFGUI/ResourceManager.cpp
	${SRC_DIR}/SFGUI/Scale.cpp
	${SRC_DIR}/SFGUI/Scrollbar.cpp
	${SRC_DIR}/SFGUI/ScrolledWindow.cpp
	${SRC_DIR}/SFGUI/Selector.cpp
	${SRC_DIR}/SFGUI/Separator.cpp
	${SRC_DIR}/SFGUI/SFGUI.cpp
	${SRC_DIR}/SFGUI/Signal.cpp
	${SRC_DIR}/SFGUI/Spinner.cpp
	${SRC_DIR}/SFGUI/Table.cpp
	${SRC_DIR}/SFGUI/TableCell.cpp
	${SRC_DIR}/SFGUI/TableOptions.cpp
	${SRC_DIR}/SFGUI/ToggleButton.cpp
	${SRC_DIR}/SFGUI/Viewport.cpp
	${SRC_DIR}/SFGUI/Widget.cpp
	${SRC_DIR}/SFGUI/Window.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )
include_directories( ${OPENGL_INCLUDE_DIR} )
include_directories( "${PROJECT_SOURCE_DIR}/extlibs/libELL/include" )
include_directories( "${PROJECT_SOURCE_DIR}/extlibs/GLee/include" )

### GLee ###

set(
	SOURCES
	${SOURCES}
	${PROJECT_SOURCE_DIR}/extlibs/GLee/src/GLee.c
)

set_source_files_properties( ${PROJECT_SOURCE_DIR}/extlibs/GLee/src/GLee.c PROPERTIES COMPILE_FLAGS "-w" )

# Static runtime linkage for our favorite compiler.
if( MSVC AND STATIC_STD_LIBS )
	foreach( flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO )
		if( ${flag} MATCHES "/MD" )
			string( REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}" )
		endif()
	endforeach()
endif()

# Add the library.
if( BUILD_SHARED_LIBS )
	add_library( sfgui SHARED ${SOURCES} )

	set_target_properties( sfgui PROPERTIES DEBUG_POSTFIX -d )

	if ( WIN32 AND CMAKE_COMPILER_IS_GNUCXX )
		set_target_properties( sfgui PROPERTIES PREFIX "" )
		set_target_properties( sfgui PROPERTIES IMPORT_SUFFIX ".a" )
	endif()
else()
	add_definitions( -DSFGUI_STATIC )
	
	add_library( sfgui ${SOURCES} )

	set_target_properties( sfgui PROPERTIES DEBUG_POSTFIX -s-d )
	set_target_properties( sfgui PROPERTIES RELEASE_POSTFIX -s )
	set_target_properties( sfgui PROPERTIES MINSIZEREL_POSTFIX -s )
endif()

# Tell the compiler to export when necessary.
set_target_properties( sfgui PROPERTIES DEFINE_SYMBOL SFGUI_EXPORTS )

target_link_libraries( sfgui ${SFML_GRAPHICS_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_SYSTEM_LIBRARY} ${OPENGL_gl_LIBRARY} )

### EXAMPLES ###

if( BUILD_EXAMPLES )
	add_subdirectory( "examples" )
endif()

### INSTALL TARGETS ###

install(
	TARGETS sfgui
	RUNTIME DESTINATION bin COMPONENT bin
	LIBRARY DESTINATION lib COMPONENT bin
	ARCHIVE DESTINATION lib COMPONENT dev
)

install(
	DIRECTORY include
	DESTINATION .
)

install(
	FILES README AUTHORS LICENSE
	DESTINATION ${SHARE_TARGET_DIR}
)
