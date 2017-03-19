#cmake 必要バージョン
cmake_minimum_required(VERSION 2.6.4)
# プロジェクト名
project(kuikR)
#バージョン番号
SET(serial "1.0.0")
#ビルドタイプ
SET(CMAKE_BUILD_TYPE release)
#インストール場所
SET(CMAKE_INSTALL_PREFIX /usr/bin)


###### EXECUTABLE&SORCE_DEFINE #####
#作成ターゲットの設定 
SET(MAIN main.c window.c)
SET(COMPILE_SORCE ${MAIN} )


#GTKの設定
include(FindPkgConfig)
pkg_check_modules(GMODULE gmodule-2.0)
pkg_check_modules(GTK gtk+-2.0)
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS} ${PROJECT_LIBRARY_DIR})
link_libraries(${GTK_LIBRARIES} )



###### EXECUTABLE&SORCE_DEFINE #####
# 実行ファイルの生成
add_executable(${TARGET_EXE} ${COMPILE_SORCE})

# ライブラリのリンクの設定
target_link_libraries(${TARGET_EXE} ${TARGET_LIBS})
