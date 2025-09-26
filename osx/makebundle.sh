#!/bin/sh

rm -rf RUBIRC.app
rm -f *.app.zip

python $HOME/.local/bin/gtk-mac-bundler rubirc.bundle

echo "Compressing bundle"
#hdiutil create -format UDBZ -srcdir RUBIRC.app -quiet RUBIRC-2.9.6.1-$(git rev-parse --short master).dmg
zip -9rXq ./RUBIRC-$(git describe --tags).app.zip ./RUBIRC.app

