{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.go
    pkgs.qt6.qtbase
    pkgs.cmake
    pkgs.swig
  ];

  shellHook = ''
    echo "Setting up Go environment..."

    # Setting up Go environment variables
    export GOPATH=$HOME/go
    export PATH=$GOPATH/bin:$PATH

    echo "Go environment and Cursor with extensions are ready."
  '';
}
