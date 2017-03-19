#cmake 必要バージョン
cmake_minimum_required(VERSION 2.6.4)
# プロジェクト名
#####共有ライブラリの作成
project(kuikR)
#バージョン番号
SET(serial "1.0.0")
#ビルドタイプ
SET(CMAKE_BUILD_TYPE release)
#インストール場所
SET(CMAKE_INSTALL_PREFIX /usr/bin)

# SHARED Libraryのバージョン
SET(soserial "1.0.0")

###### EXECUTABLE&SORCE_DEFINE #####
## 元となるソースSET
#SET(PALLET pallet_create.c)
#SET(PALLET_TEST pallet_test.c)
#SET(TEST_FUNCTION ${PALLET} ${PALLET_TEST})

##ライブラリの作成
#add_library(${FUNCTION_LIB_TEST} SHARED ${TEST_FUNCTION})


