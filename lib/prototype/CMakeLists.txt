set (CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow "
               "-Wpointer-arith -Wcast-qual "
               "-ggdb -fprofile-arcs -ftest-coverage --std=c++0x " )

add_definitions( ${CXX_FLAGS} )

# NOTE use it if you have custom QT installation
set ( QT_QMAKE_EXECUTABLE "/home/denes/ROXAR/dev/dmatetelki/depot/packages/linux-amd64-gcc_4_4/qt-4_7_1_patched2/bin/qmake" )
# NOTE you need a qt.conf in the same dir as the qmake, with the contents:
# [Paths]
# Prefix=/home/denes/ROXAR/dev/dmatetelki/depot/packages/linux-amd64-gcc_4_4/qt-4_7_1_patched2
# Documentation=doc
# Headers=include
# Libraries=lib/debug
# Binaries=bin
# Plugins=plugins
# Imports=imports
# Data=
# Translations=
# Settings=
# Examples=



FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
QT4_WRAP_CPP(prototype_HEADERS_MOC widget.hpp)

# set(CMAKE_AUTOMOC ON)D

include_directories (. ../../lib )

add_executable ( prototype main.cpp widget.cpp ${prototype_HEADERS_MOC} )
target_link_libraries ( prototype CppUtils ${QT_LIBRARIES} pthread)

add_custom_target( proto
                   DEPENDS prototype
)