cmake_minimum_required(VERSION 3.10)
project(_5)

SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_NO_BOOST_CMAKE ON)


FIND_PACKAGE(Threads)
FIND_PACKAGE(LibArchive)
FIND_PACKAGE(ICU REQUIRED COMPONENTS uc i18n)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem locale system)

IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF (Boost_FOUND)

IF (ICU_FOUND)
    INCLUDE_DIRECTORIES(${ICU_INCLUDE_DIRS})
    LINK_DIRECTORIES(${ICU_LIBRARY_DIRS})
ENDIF (ICU_FOUND)

INCLUDE_DIRECTORIES(${LibArchive_INCLUDE_DIR} headers sources)

ADD_EXECUTABLE(_5_one_thread sources/one_thread_solution.cpp
        sources/archive_functions.cpp
        sources/configuration.cpp
        headers/configuration.h
        sources/work_with_text_file.cpp
        headers/work_with_text_file.h
<<<<<<< HEAD
        headers/time_functions.h sources/directory_functions.cpp
        headers/directory_functions.h
        headers/dispatcher.h sources/dispatcher.cpp
        sources/some_functions_for_one_thread_solution.cpp
        headers/some_functions_for_one_thread_solution.h)
=======
        headers/time_functions.h sources/directory_functions.cpp headers/directory_functions.h
        headers/dispatcher.h sources/dispatcher.cpp)
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375

ADD_EXECUTABLE(_5_multi_thread sources/multi_thread_solution.cpp
        sources/archive_functions.cpp
        sources/configuration.cpp
        headers/configuration.h
        sources/work_with_text_file.cpp
        headers/work_with_text_file.h
<<<<<<< HEAD
        headers/time_functions.h headers/dispatcher.h
        sources/directory_functions.cpp
        headers/directory_functions.h
        sources/dispatcher.cpp)
=======
        headers/time_functions.h headers/dispatcher.h sources/directory_functions.cpp
        headers/directory_functions.h sources/dispatcher.cpp)
>>>>>>> 6565b9f1ae3fcf991cb7fc98f27c6ad1431b9375

IF (UNIX)
    TARGET_LINK_LIBRARIES(_5_one_thread libarchive.so ${Boost_LIBRARIES} ${ICU_LIBRARIES} Threads::Threads)
    TARGET_LINK_LIBRARIES(_5_multi_thread libarchive.so ${Boost_LIBRARIES} ${ICU_LIBRARIES} Threads::Threads)
ELSE (UNIX)
    TARGET_LINK_LIBRARIES(_5_one_thread libarchive ${Boost_LIBRARIES} ${ICU_LIBRARIES} Threads::Threads)
    TARGET_LINK_LIBRARIES(_5_multi_thread libarchive ${Boost_LIBRARIES} ${ICU_LIBRARIES} Threads::Threads)
ENDIF (UNIX)