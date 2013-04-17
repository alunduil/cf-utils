add_executable(test_account test_account.c)
target_link_libraries(test_account cf-bindings)
target_link_libraries(test_account ${CHECK_LIBRARY})
