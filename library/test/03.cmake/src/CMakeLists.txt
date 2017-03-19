#cmake 必要バージョン
cmake_minimum_required(VERSION 2.8)
# プロジェクト名
project(library_test)
#バージョン番号
SET(serial "1.0.0")
#ビルドタイプ
SET(CMAKE_BUILD_TYPE release)
#インストール場所
SET(CMAKE_INSTALL_PREFIX /usr/bin)

###### EXECUTABLE&SORCE_DEFINE #####
#作成ターゲットの設定 
SET(MAIN main.c)
SET(COMPILE_SORCE ${MAIN})


#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(${PROJECT_LIBRARY_DIR})

#SET(PROJECT_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib)

###### EXECUTABLE&SORCE_DEFINE #####
# 実行ファイルの生成
add_executable(${TARGET_EXE} ${COMPILE_SORCE})

# ライブラリのリンクの設定
link_libraries(${PROJECT_LIBRARY_DIR} ${TARGET_LIB})
target_link_libraries(${TARGET_EXE} ${TARGET_LIB})
