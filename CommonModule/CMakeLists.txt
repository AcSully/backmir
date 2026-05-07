set(CM_SOURCES
    base64.cpp
    ByteBuffer.cpp
    cJSON.c
    CollDownController.cpp
    CommandLineHelper.cpp
    ConsoleHelper.cpp
    ConvertUTF.c
    DataEncryptor.cpp
    DataParser.cpp
    fileopt.cpp
    GamePacket.cpp
    GameStructSerialize.cpp
    HideAttribHelper.cpp
    LoginExtendInfoParser.cpp
    LuaBaseEngine.cpp
    LuaBaseEngine_Dispatcher.cpp
    LuaBaseEngine_ScriptLoader.cpp
    LuaBaseExecutor.cpp
    LuaConfigLoader.cpp
    LuaDataLoader.cpp
    LuaEventDispatcher.cpp
    lua_extend.cpp
    LuaIterator.cpp
    MagicEffectID.cpp
    MapConfigManager.cpp
    QuestContext.cpp
    MirMap.cpp
    ProtoType.cpp
    RandGenerator.cpp
    SaveFile.cpp
    SettingLoader.cpp
    ShareData.cpp
    SKnl3Helper.cpp
    StateController.cpp
    utils.cpp
    xxtea.c
    ZipDataReader.cpp
    loginsvr.pb.cc
)

add_library(CommonModule STATIC ${CM_SOURCES})

target_include_directories(CommonModule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..      # lets #include "CommonModule/Foo.h" resolve
    ${CMAKE_CURRENT_SOURCE_DIR}         # lets internal files do #include "Foo.h"
    ${LUAJIT_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(CommonModule PUBLIC
    Threads::Threads
    ${LUAJIT_LIBRARIES}
    ${TOLUA_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ZLIB::ZLIB
    CURL::libcurl
    SQLite::SQLite3
)

if(WIN32)
    if(ZIPARCHIVE_LIBRARIES)
        target_include_directories(CommonModule PUBLIC ${ZIPARCHIVE_INCLUDE_DIRS})
        target_link_libraries(CommonModule PUBLIC ${ZIPARCHIVE_LIBRARIES})
    endif()
else()
    if(LIBZIP_FOUND)
        target_include_directories(CommonModule PUBLIC ${LIBZIP_INCLUDE_DIRS})
        target_link_libraries(CommonModule PUBLIC ${LIBZIP_LINK_LIBRARIES})
    endif()
endif()
