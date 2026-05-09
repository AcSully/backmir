cmake_minimum_required(VERSION 3.16)
project(BackMIR VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-fno-operator-names)

# ---------------------------------------------------------------------------
# Build output mirrors the VS layout: ../BackMir/Bin (Release) / BinDebug (Debug)
# ---------------------------------------------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BM_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/../BackMir/BinDebug")
else()
    set(BM_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/../BackMir/Bin")
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BM_OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BM_OUTPUT_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BM_OUTPUT_DIR}/lib")

# ---------------------------------------------------------------------------
# Global compile definitions
# ---------------------------------------------------------------------------
add_compile_definitions(
    _NET_GAME_
    _LUAJIT_
    _BIN_PATH
    _DISABLE_CONSOLE          # suppress Win32 console helper on Linux
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
else()
    add_compile_definitions(NDEBUG)
endif()

# ---------------------------------------------------------------------------
# Find third-party packages
# ---------------------------------------------------------------------------
find_package(Threads REQUIRED)

find_package(PkgConfig QUIET)

# libevent
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBEVENT libevent)
else()
    find_library(LIBEVENT_LIBRARIES NAMES event)
    find_path(LIBEVENT_INCLUDE_DIRS event2/event.h)
endif()
if(NOT LIBEVENT_FOUND AND NOT LIBEVENT_LIBRARIES)
    message(WARNING "libevent not found — install libevent-dev")
endif()

# glog — use pkg-config (libglog.pc is present on Ubuntu)
find_package(glog QUIET)
if(NOT glog_FOUND)
    pkg_check_modules(GLOG libglog)
    if(GLOG_FOUND)
        add_library(glog::glog UNKNOWN IMPORTED)
        set_target_properties(glog::glog PROPERTIES
            IMPORTED_LOCATION "${GLOG_LINK_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${GLOG_INCLUDE_DIRS}"
            INTERFACE_COMPILE_OPTIONS "${GLOG_CFLAGS_OTHER}")
    else()
        message(WARNING "glog not found — install libgoogle-glog-dev")
        add_library(glog::glog INTERFACE IMPORTED)
    endif()
endif()

# SQLite3 — use pkg-config (sqlite3.pc is present on Ubuntu)
find_package(SQLite3 QUIET)
if(NOT SQLite3_FOUND)
    pkg_check_modules(SQLITE3 sqlite3)
    if(SQLITE3_FOUND)
        add_library(SQLite::SQLite3 UNKNOWN IMPORTED)
        set_target_properties(SQLite::SQLite3 PROPERTIES
            IMPORTED_LOCATION "${SQLITE3_LINK_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${SQLITE3_INCLUDE_DIRS}")
    else()
        message(WARNING "SQLite3 not found — install libsqlite3-dev")
        add_library(SQLite::SQLite3 INTERFACE IMPORTED)
    endif()
endif()

# zlib
find_package(ZLIB REQUIRED)

# Protobuf — prefer /opt/protobuf-3.5.1 if present, fall back to system
if(EXISTS "/opt/protobuf-3.5.1")
    set(PROTOBUF_ROOT "/opt/protobuf-3.5.1")
    set(Protobuf_INCLUDE_DIR "${PROTOBUF_ROOT}/include")
    set(Protobuf_LIBRARY     "${PROTOBUF_ROOT}/lib/libprotobuf.a")
    set(Protobuf_PROTOC_EXECUTABLE "${PROTOBUF_ROOT}/bin/protoc")
    set(PROTOBUF_INCLUDE_DIRS "${Protobuf_INCLUDE_DIR}")
    set(PROTOBUF_LIBRARIES    "${Protobuf_LIBRARY}")
    find_package(Protobuf REQUIRED HINTS "${PROTOBUF_ROOT}/lib/cmake/protobuf")
else()
    find_package(Protobuf REQUIRED)
endif()

# libcurl
find_package(CURL REQUIRED)

# LuaJIT — use pkg-config (luajit.pc is present on Ubuntu)
pkg_check_modules(LUAJIT luajit)
if(LUAJIT_FOUND)
    set(LUAJIT_LIBRARIES    "${LUAJIT_LINK_LIBRARIES}")
    set(LUAJIT_INCLUDE_DIRS "${LUAJIT_INCLUDE_DIRS}")
else()
    find_library(LUAJIT_LIBRARIES NAMES luajit-5.1 luajit lua51 lua5.1 lua)
    find_path(LUAJIT_INCLUDE_DIRS NAMES luajit.h lua.h
              PATH_SUFFIXES luajit-2.1 luajit-2.0 lua5.1 lua)
    if(NOT LUAJIT_LIBRARIES)
        message(WARNING "LuaJIT not found — install libluajit-5.1-dev")
        set(LUAJIT_LIBRARIES "")
        set(LUAJIT_INCLUDE_DIRS "")
    endif()
endif()

# tolua++ — library is libtolua++5.1.a in /usr/lib on Ubuntu
find_library(TOLUA_LIBRARIES NAMES tolua++5.1 tolua++ tolua
             PATHS /usr/lib /usr/local/lib)
find_path(TOLUA_INCLUDE_DIRS NAMES tolua++.h
          PATHS /usr/include /usr/local/include)
if(NOT TOLUA_LIBRARIES)
    message(WARNING "tolua++ not found — install libtolua++5.1-dev")
    set(TOLUA_LIBRARIES "")
    set(TOLUA_INCLUDE_DIRS "")
endif()

# ZipArchive (Windows) / libzip (Linux)
if(WIN32)
    find_library(ZIPARCHIVE_LIBRARIES NAMES ZipArchive QUIET)
    find_path(ZIPARCHIVE_INCLUDE_DIRS ZipArchive.h QUIET)
else()
    find_package(PkgConfig QUIET)
    pkg_check_modules(LIBZIP libzip)
    if(NOT LIBZIP_FOUND)
        message(WARNING "libzip not found — install libzip-dev")
        set(LIBZIP_LIBRARIES "")
        set(LIBZIP_INCLUDE_DIRS "")
    endif()
endif()

# ---------------------------------------------------------------------------
# Subprojects
# ---------------------------------------------------------------------------
add_subdirectory(CommonModule)
add_subdirectory(BMServer)
