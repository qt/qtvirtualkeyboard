#
# Automatically detects the T9Write build directory and sets the following variables:
#
#   T9WRITE_BUILD_DIR: A base directory for the architecture specific build directory
#   T9WRITE_ALPHABETIC_OBJ: Absolute path to the target object file
#

!isEmpty(CROSS_COMPILE) {
    T9WRITE_BUILD_DIR = $$files(build_Android_ARM*)
} else:linux {
    T9WRITE_BUILD_DIR = $$files(build_Android_x86*)
} else:win32 {
    T9WRITE_BUILD_DIR = $$files(build_VC*)
}

isEmpty(T9WRITE_BUILD_DIR): error(T9Write SDK could not be detected. Please make sure you have extracted the contents of the T9Write SDK to $$PWD)
!count(T9WRITE_BUILD_DIR, 1): error(Conflicting T9Write build directories found: $$T9WRITE_BUILD_DIR)

T9WRITE_ALPHABETIC_OBJ = $$PWD/$$files($$T9WRITE_BUILD_DIR/objects/t9write_alphabetic*.o*)

count(T9WRITE_BUILD_DIR, 0): error(T9Write object file is missing for the target $$T9WRITE_BUILD_DIR)
!count(T9WRITE_BUILD_DIR, 1): error(Multiple T9Write object files found for the target $$T9WRITE_BUILD_DIR)
