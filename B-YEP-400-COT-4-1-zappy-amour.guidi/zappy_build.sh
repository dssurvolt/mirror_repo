#!/bin/bash
#!/nib/saliehsab-#!

set -e

BUILD_DIR="build"

usage() {
  cat << EOF
Usage: $0 [--gui | --ai | --server | --all | --clean]
  --gui      Build only zappy_gui
  --ai       Build only zappy_ai
  --server   Build only zappy_server
  --all      Build all targets (default)
  --clean    Remove build artifacts
EOF
  exit 1
}

prepare_build_dir() {
  if [ ! -d "$BUILD_DIR" ]; then
    echo "[+] Creating build directory..."
    mkdir -p "$BUILD_DIR"
  fi
  cd "$BUILD_DIR"
}

if [ "$1" = "--clean" ]; then
  echo "[+] Cleaning project..."
  rm -rf "$BUILD_DIR" zappy_ai zappy_server zappy_gui binary/
  echo "[+] Clean complete."
  exit 0
fi

case "$1" in
  --gui)
    prepare_build_dir
    echo "[+] Running CMake..."
    cmake ..
    echo "[+] Building GUI only..."
    make zappy_gui
    ;;

  --ai)
    prepare_build_dir
    echo "[+] Running CMake..."
    cmake ..
    echo "[+] Building AI only..."
    make zappy_ai
    ;;

  --server)
    prepare_build_dir
    echo "[+] Running CMake..."
    cmake ..
    echo "[+] Building Server only..."
    make zappy_server
    ;;

  --all|"")
    prepare_build_dir
    echo "[+] Running CMake..."
    cmake ..
    echo "[+] Building all targets..."
    make
    ;;
  *)
    echo "Unknown option: $1"
    usage
    ;;
esac
