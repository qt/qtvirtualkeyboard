# We can't create the same interface imported target multiple times, CMake will complain if we do
# that. This can happen if the find_package call is done in multiple different subdirectories.
if(TARGET Hunspell::Hunspell)
    set(Hunspell_FOUND ON)
    return()
endif()

find_package(PkgConfig)

pkg_check_modules(hunspell hunspell IMPORTED_TARGET)
set(__hunspell_target_name "PkgConfig::hunspell")

if (NOT TARGET "${__hunspell_target_name}")
    set(Hunspell_FOUND 0)
    return()
endif()

add_library(Hunspell::Hunspell INTERFACE IMPORTED)
target_link_libraries(Hunspell::Hunspell INTERFACE ${__hunspell_target_name})
set(Hunspell_FOUND TRUE)
unset(__hunspell_target_name)


