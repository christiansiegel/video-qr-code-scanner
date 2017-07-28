cmake_minimum_required( VERSION 3.0 )
project( video-qr-code-scanner )

add_executable( video-qr-code-scanner main.cpp )
target_compile_features( video-qr-code-scanner PRIVATE cxx_range_for )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( video-qr-code-scanner ${OpenCV_LIBS} )

find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries( video-qr-code-scanner ${ZLIB_LIBRARIES} zbar )
endif( ZLIB_FOUND )

