#!/usr/bin/env bash
set -e

script_dir="$(CDPATH= cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
exec "$script_dir/GacBuild" \
    -mode:GacBuild \
    "-pathGacGen:$script_dir/GacGen" \
    "-pathCppMerge:$script_dir/CppMerge" \
    "$@"
