idf_component_register(SRC_DIRS "."
                        INCLUDE_DIRS include
                        REQUIRES bt)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-const-variable)