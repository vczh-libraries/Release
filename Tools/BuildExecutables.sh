#!/bin/bash

pushd ./Executables/CodePack
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.."
popd

pushd ./Executables/CppMerge
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.."
popd

pushd ./Executables/GlrParserGen
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.."
popd

pushd ./Executables/GacGen
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.."
popd

cp ./Executables/CodePack/Bin/CodePack .
cp ./Executables/CppMerge/Bin/CppMerge .
cp ./Executables/GlrParserGen/Bin/GlrParserGen .
cp ./Executables/GacGen/Bin/GacGen .