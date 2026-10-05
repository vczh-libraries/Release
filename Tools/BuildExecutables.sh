#!/bin/bash
set -e

cd -- "$(dirname -- "${BASH_SOURCE[0]}")"

pushd ./Executables/CodePack
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.." CPP_OPTIMIZATION=-O2
popd

pushd ./Executables/CppMerge
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.." CPP_OPTIMIZATION=-O2
popd

pushd ./Executables/GlrParserGen
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.." CPP_OPTIMIZATION=-O2
popd

pushd ./Executables/GacGen
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.." CPP_OPTIMIZATION=-O2
popd

pushd ./Executables/GitTui
make VCPROOT="$(pwd)/.." clean
make VCPROOT="$(pwd)/.." CPP_OPTIMIZATION=-O2
popd

cp ./Executables/CodePack/Bin/CodePack .
cp ./Executables/CppMerge/Bin/CppMerge .
cp ./Executables/GlrParserGen/Bin/GlrParserGen .
cp ./Executables/GacGen/Bin/GacGen .
cp ./Executables/GitTui/Bin/GitTui .
