project(clixon-plugin-tcp)
cmake_minimum_required(VERSION 3.20)


function(export_headers TARGET HEADER_SOURCE_DIR HEADER_DEST_DIR)

	message(STATUS "CONFIGURE_DEPENDS=${CONFIGURE_DEPENDS}")
	message(STATUS "HEADER_SOURCE_DIR=${HEADER_SOURCE_DIR}")

    # Put all headers that are in the source directory into EXPORT_HEADERS variable
    file(GLOB_RECURSE EXPORT_HEADERS CONFIGURE_DEPENDS 
        RELATIVE "${HEADER_SOURCE_DIR}" 
        "${HEADER_SOURCE_DIR}/*.h"
    )
	
	message(STATUS "GLOB_RECURSE=${EXPORT_HEADERS}")

    # For each header that will be exported
    foreach(HEADER ${EXPORT_HEADERS})
		message(STATUS "Processing ${HEADER}")

        # Get the directory portion that needs to be created        
        get_filename_component(HEADER_DIRECTORY "${HEADER}" DIRECTORY)
		
		string(MAKE_C_IDENTIFIER "${HEADER_DEST_DIR}/${HEADER}" TARGET_NAME)
		
		# message(STATUS "HEADER_DIRECTORY=${HEADER_DIRECTORY}")

        # create the directory  
        # add_custom_command("${TARGET_NAME}_folder"
        #     COMMAND ${cmake_command} -e make_directory "${header_dest_dir}/${header_directory}"
        #)
		
		message(STATUS "Make directory ${HEADER_DEST_DIR}/${HEADER_DIRECTORY}")

		

		add_custom_command(
			OUTPUT "${HEADER_DEST_DIR}/${HEADER}"
			COMMAND ln -sf "${HEADER_SOURCE_DIR}/${HEADER}" "${HEADER_DEST_DIR}/${HEADER}"
			VERBATIM
		)
		
		add_custom_target(
			${TARGET_NAME} ALL 
			DEPENDS "${HEADER_DEST_DIR}/${HEADER}" 
			VERBATIM
		)
		
		add_dependencies(${TARGET} ${TARGET_NAME})


		# Make a hard link to the file
		# add_custom_command(
		#	TARGET ${TARGET} PRE_BUILD
		#	COMMAND if not exist "${HEADER_DEST_DIR}/${HEADER}" \( mklink /h "${HEADER_DEST_DIR}/${HEADER}" "${HEADER_SOURCE_DIR}/${HEADER}" \) 
		#)
		
		message(STATUS "Make Link ${HEADER_DEST_DIR}/${HEADER} to ${HEADER_SOURCE_DIR}/${HEADER}")

        # else()
		# 
        #     # Make a symbolic link to the file
        #     add_custom_command(TARGET ${TARGET} PRE_BUILD
        #         COMMAND ln -sf "${HEADER_SOURCE_DIR}/${HEADER}" "${HEADER_DEST_DIR}/${HEADER}"
        #     )


    endforeach(HEADER)

endfunction()


set(CMAKE_SYSTEM_NAME QNX)

set(arch gcc_ntox86_64)
set(CMAKE_CXX_COMPILER q++)
set(CMAKE_CXX_COMPILER_TARGET ${arch})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fPIC -DHAVE_CONFIG_H -fopenmp -D_DEBUG")

set(BASE_PATH "${PROJECT_SOURCE_DIR}/..")
set(CLIGEN_PATH "${BASE_PATH}/cligen")
set(CLIXON_PATH "${BASE_PATH}/clixon")
set(QNX_BASE_PATH "$ENV{UserProfile}/qnx700")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "BASE_PATH=${BASE_PATH}")
message(STATUS "CLIGEN_PATH=${CLIGEN_PATH}")
message(STATUS "CLIXON_PATH=${CLIXON_PATH}")
message(STATUS "QNX_BASE_PATH=${QNX_BASE_PATH}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")


file(GLOB_RECURSE SOURCES *.cpp)
include_directories(${BASE_PATH} ${CLIXON_PATH}/lib ${CLIXON_PATH}/apps/backend ${CMAKE_CURRENT_BINARY_DIR}/include)


set(CMAKE_FIND_LIBRARY_SUFFIXES .so .so.5 .so.5.2 .so.4)
find_library(lcxx 			 	libc++				PATHS $ENV{UserProfile}/qnx700/target/qnx7/x86_64/usr/lib NO_DEFAULT_PATH)
# find_library(lcc 		 		libc				PATHS $ENV{UserProfile}/qnx700/target/qnx7/x86_64/usr/lib NO_DEFAULT_PATH)

find_library(lcligen 			libcligen 			PATHS ${CLIGEN_PATH}				NO_DEFAULT_PATH)

find_library(lclixon_backend 	libclixon_backend 	PATHS ${CLIXON_PATH}/apps/backend	NO_DEFAULT_PATH)
find_library(lclixon 			libclixon 			PATHS ${CLIXON_PATH}/lib/src/		NO_DEFAULT_PATH)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
set(CMAKE_SHARED_LIBRARY_SUFFIX .so)
target_link_libraries(${PROJECT_NAME} ${lclixon_backend} ${lcligen} ${lclixon} ${lcxx} ${lcc})

export_headers(${PROJECT_NAME} ${CLIXON_PATH}/apps/backend ${CMAKE_CURRENT_BINARY_DIR}/include/clixon)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)

