set(PREV_LIBNAME "${LIBRARY_PREFIX}${PREV_TEST_NAME}_lib${LIBRARY_SUFFIX}")
set(NEW_LIBNAME  "${LIBRARY_PREFIX}${example}_lib${LIBRARY_SUFFIX}")
set(CLIENT       "${example}${CLIENTSUFFIX}")
set(TEST_NAME    "${example}-new-client-with-old-lib")

add_custom_target(
    ${TEST_NAME} ALL
        ${CMAKE_COMMAND} -E make_directory ${TEST_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${EXAMPLES_BIN_DIR}/${CLIENT} ${EXAMPLES_BIN_DIR}/${TEST_NAME}/${CLIENT}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${EXAMPLES_BIN_DIR}/${PREV_LIBNAME} ${EXAMPLES_BIN_DIR}/${TEST_NAME}/${NEW_LIBNAME}
        DEPENDS ${example} ${PREV_TEST_NAME}
        WORKING_DIRECTORY ${EXAMPLES_BIN_DIR}
)

add_test(NAME ${TEST_NAME}
    COMMAND ${EXAMPLES_BIN_DIR}/${TEST_NAME}/${CLIENT}
)

