cmake_policy(SET CMP0063 NEW)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# These values are difficult to get using CMake and so hardcoding
if (WIN32)
	set(CLIENTSUFFIX ".exe")
	set(LIBRARY_PREFIX "")
	set(LIBRARY_SUFFIX ".dll")
else ()
	set(CLIENTSUFFIX "")
	set(LIBRARY_PREFIX "lib")
	set(LIBRARY_SUFFIX ".so")
endif()

set(PUB_FILE_BASE_NAMES
    example # File name without extension
)
set(LIB_GLUE_SRCS
    ${LIB_GLUE_SRCS_EXTRA}
    ${example_ROOT}/cib/__zz_cib_Example-gateway.cpp
    ${example_ROOT}/cib/__zz_cib_Example-classId-repo.cpp
    ${example_ROOT}/cib/__zz_cib_Example-decl.h
    ${example_ROOT}/cib/__zz_cib_Example-export.h
    ${example_ROOT}/cib/__zz_cib_Example-ids.h
    ${example_ROOT}/cib/__zz_cib_Example-mtable.h
    ${example_ROOT}/cib/__zz_cib_Example-mtable-helper.h
)
set(PUB_FILES "")
set(EXP_SOURCES "")
set(TEST_CMD ${CLIENTNAME})
set(CIBCMD ${CMAKE_BINARY_DIR}/cib -i pub -o exp -b cib -m Example)
set(DEPENDS cib ${example}GlueCode)
set(EXAMPLES_BIN_DIR ${CMAKE_BINARY_DIR}/examples)

include("${example}/Prologue.cmake")

foreach(PUBFILE ${PUB_FILE_BASE_NAMES})
    list(APPEND LIB_GLUE_SRCS ${example_ROOT}/cib/${PUBFILE}.h.cpp)
    list(APPEND PUB_FILES ${example_ROOT}/pub/${PUBFILE}.h)
    list(APPEND EXP_HEADERS ${example_ROOT}/exp/${PUBFILE}.h)
    list(APPEND EXP_SOURCES ${example_ROOT}/exp/${PUBFILE}.cpp)
endforeach()

list(APPEND EXAMPLE_HEADERS ${PUB_FILES})
foreach(CIBOUTFILE ${LIB_GLUE_SRCS})
    set_source_files_properties(${CIBOUTFILE} GENERATED)
endforeach()

foreach(CIBOUTFILE ${EXP_HEADERS})
    set_source_files_properties(${CIBOUTFILE} GENERATED)
endforeach()

foreach(CIBOUTFILE ${EXP_SOURCES})
    set_source_files_properties(${CIBOUTFILE} GENERATED)
endforeach()

set(LIB_SOURCES
    ${example_ROOT}/src/example-lib.cpp
)

set(CLIENT_SOURCES
    ${example_ROOT}/src/example-client.cpp
    example-main.cpp
)

add_library(${LIBNAME}
    SHARED
        ${LIB_SOURCES}
        ${PUB_FILES}
        ${LIB_GLUE_SRCS}
)
set_target_properties(${LIBNAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
)

target_include_directories(${LIBNAME}
    PRIVATE
        ${example_ROOT}/pub
)
add_dependencies(${LIBNAME} cib ${example}GlueCode ${DEPENDS})

add_executable(${CLIENTNAME}
    ${CLIENT_SOURCES}
    ${EXP_SOURCES}
)

add_test(NAME ${CLIENTNAME} COMMAND ${TEST_CMD})

add_custom_command(
    OUTPUT ${LIB_GLUE_SRCS} ${EXP_SOURCES}
    COMMAND echo Running cib...
    COMMAND ${CIBCMD}
    COMMAND echo Generated files: ${LIB_GLUE_SRCS}
    DEPENDS cib CibResources ${PUB_FILES} ${DEPENDS}
    WORKING_DIRECTORY ${example_ROOT}
)
add_custom_target(${example}GlueCode DEPENDS ${LIB_GLUE_SRCS})

target_include_directories(${CLIENTNAME}
    PRIVATE
        ${example_ROOT}/exp
)
target_link_libraries(${CLIENTNAME}
    PRIVATE
        ${LIBNAME}
)
if(MSVC)
    set_target_properties(${CLIENTNAME} PROPERTIES LINK_FLAGS "${LINK_FLAGS} /INCREMENTAL:NO")
endif()

if(NOT MSVC)
    include("${example}/DocCommands.cmake")
    add_dependencies(ExamplesReadme ${example}_ReadMe)
endif()

include("${example}/Epilogue.cmake")
