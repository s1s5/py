
add_executable(builtins_enumerate test_enumerate.cpp ${CPPUT_MAIN})
target_link_libraries(builtins_enumerate ${CPPUT_LIBS})

add_test(NAME builtins_enumerate
  COMMAND builtins_enumerate)
