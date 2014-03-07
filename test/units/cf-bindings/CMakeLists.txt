add_executable(check_account check_account.c)
target_link_libraries(check_account check cf-bindings)
add_test(check_account ${EXECUTABLE_OUTPUT_PATH}/check_account)

#add_executable(check_authentication check_authentication.c)
#target_link_libraries(check_authentication check)
#add_test(check_authentication ${EXECUTABLE_OUTPUT_PATH}/check_authentication)
#
#add_executable(check_container check_container.c)
#target_link_libraries(check_container check)
#add_test(check_container ${EXECUTABLE_OUTPUT_PATH}/check_container)
#
#add_executable(check_object check_object.c)
#target_link_libraries(check_object check)
#add_test(check_object ${EXECUTABLE_OUTPUT_PATH}/check_object)
