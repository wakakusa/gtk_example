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
# SHARED Libraryのバージョン
SET(soserial "1.0.0")

SET(ADD library1.c)
SET(COMPILE_SORCE ${ADD})


# 生成するライブラリ名，元となるソース
# SHARED Libraryの場合
 add_library(${TARGET_LIB1} SHARED ${COMPILE_SORCE})


