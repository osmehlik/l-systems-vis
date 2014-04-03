#!/bin/bash
# Based on https://qt-project.org/doc/qt-5.0/qtdoc/deployment-mac.html

APP="L-SystemsVis"
QT_PATH="/Users/olda/Qt/5.2.1/clang_64"

make clean
$QT_PATH/bin/qmake -config release
make
$QT_PATH/bin/macdeployqt $APP.app -dmg

