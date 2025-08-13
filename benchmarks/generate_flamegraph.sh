#!/usr/bin/env bash
set -euo pipefail

# === Configuration ===
# Update this path to match where you cloned Brendan Gregg's FlameGraph repo
FLAMEGRAPH_DIR="/home/saddy/code/GitHub/Flamegraph"

# Check for required tools
command -v perf >/dev/null || { echo "Error: perf not found."; exit 1; }
[[ -x "${FLAMEGRAPH_DIR}/stackcollapse-perf.pl" ]] || \
    { echo "Error: stackcollapse-perf.pl not found in ${FLAMEGRAPH_DIR}."; exit 1; }
[[ -x "${FLAMEGRAPH_DIR}/flamegraph.pl" ]] || \
    { echo "Error: flamegraph.pl not found in ${FLAMEGRAPH_DIR}."; exit 1; }

# === Usage ===
if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <app> [args...]"
  exit 1
fi

APP="$1"
shift
ARGS=("$@")

# Output filenames
PERF_DATA="perf.data"
FOLDED="out.folded"
SVG="flamegraph.svg"

# Remove pre-existing outputs
rm -f "${PERF_DATA}" "${FOLDED}" "${SVG}"

echo " == Profiling: ${APP} ${ARGS[*]} =="
# High-frequency sampling with backtrace capture using DWARF for depth
perf record -F 999 --call-graph dwarf -- "${APP}" "${ARGS[@]}"

echo " == Generating folded stacks =="
perf script > perf.script
"${FLAMEGRAPH_DIR}/stackcollapse-perf.pl" perf.script > "${FOLDED}"

echo " == Generating flamegraph SVG =="
"${FLAMEGRAPH_DIR}/flamegraph.pl" \
  --width 30000 \
  --fontsize 9 \
  --title "Flamegraph for ${APP}" \
  --countname "samples" \
  "${FOLDED}" > "${SVG}"

echo "Flamegraph generated: ${SVG}"
