#!/usr/bin/env bash
set -e

APP=$1
shift

echo " == Profiling: $APP $@ =="

perf record -F 999 --call-graph dwarf -- "$APP" "$@"

echo " == Generating flamegraph SVG =="
perf script | stackcollapse-perf.pl | flamegraph.pl > flamegraph.svg
echo "Flamegraph generated: flamegraph.svg"
