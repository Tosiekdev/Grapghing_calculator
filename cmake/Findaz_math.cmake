set(FIND_AZ_MATH_PATHS /home/tosiek/Documents/II_semestr/PP2/az_math_library)

find_path(AZ_MATH_INCLUDE_DIR azmath.h
        PATH_SUFFIXES include
        PATHS ${FIND_AZ_MATH_PATHS})

find_library(AZ_MATH_LIBRARY
        NAMES az_math
        PATH_SUFFIXES lib
        PATHS ${FIND_AZ_MATH_PATHS})