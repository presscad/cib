project(client-calls-library)

cmake_minimum_required(VERSION 3.4)

include("../../../../common/cmake/conf.cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/demo/client-calls)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/demo/client-calls)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/demo/client-calls)

set(LIBRARY_PUB_FILE_NAMES
	A.h
)

set(CIB_OUTPUT
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-gateway.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-decl.h
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-export.h
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-ids.h
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-mtable.h
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-mtable-helper.h
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-classId-repo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-proxy.h
	${CMAKE_CURRENT_SOURCE_DIR}/cib/__zz_cib_Demo-proxy-mgr.h
	${CMAKE_CURRENT_SOURCE_DIR}/exp/__zz_cib_internal/__zz_cib_Demo-ids.h
	${CMAKE_CURRENT_SOURCE_DIR}/exp/__zz_cib_internal/A-postdef.h
	${CMAKE_CURRENT_SOURCE_DIR}/exp/__zz_cib_internal/A-predef.h
	${CMAKE_CURRENT_SOURCE_DIR}/exp/A.h
)
set(LIBRARY_PUB_FILES "")
foreach(PUBFILE ${LIBRARY_PUB_FILE_NAMES})
	list(APPEND CIB_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/cib/${PUBFILE}.cpp)
	list(APPEND LIBRARY_PUB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/pub/${PUBFILE})
endforeach()
foreach(CIBOUTFILE ${CIB_OUTPUT})
	set_source_files_properties(${CIBOUTFILE} GENERATED)
endforeach()
add_custom_command(
	OUTPUT ${CIB_OUTPUT}
	COMMAND echo Running cib...
	COMMAND ${CMAKE_BINARY_DIR}/cib -i pub -o exp -b cib -m Demo -c ${CMAKE_CURRENT_SOURCE_DIR}/abi/__zz_cib_Demo-ids.h
	COMMAND echo Generated files: ${CIB_OUTPUT}
	DEPENDS cib ${LIBRARY_PUB_FILES}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(LIBRARY_SOURCES
	A.cpp
)
add_library(client-calls-library_cibified
	SHARED
		${LIBRARY_SOURCES}
		${LIBRARY_PUB_FILES}
		${CIB_OUTPUT}
)
set_target_properties(client-calls-library_cibified
	PROPERTIES
		COMPILE_DEFINITIONS LIBRARYAPI=
)
target_include_directories(client-calls-library_cibified
	PRIVATE
		pub
)
add_dependencies(client-calls-library_cibified cib)

add_library(client-calls-library
	SHARED
		${LIBRARY_SOURCES}
		${LIBRARY_PUB_FILES}
)
set_target_properties(client-calls-library
	PROPERTIES
		COMPILE_DEFINITIONS LIBRARYAPI=${DLLEXPORT}
)

target_include_directories(client-calls-library
	PUBLIC
		pub
)
if(MSVC)
    set_target_properties(client-calls-library PROPERTIES LINK_FLAGS "${LINK_FLAGS} /INCREMENTAL:NO")
    set_target_properties(client-calls-library_cibified PROPERTIES LINK_FLAGS "${LINK_FLAGS} /INCREMENTAL:NO")
endif()
