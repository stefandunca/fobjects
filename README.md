# Foreign Objects

## Swig

[Running swig with go](https://www.swig.org/Doc4.0/Go.html#Go_running_swig)
[Swig Director Classes](https://www.swig.org/Doc4.0/Go.html#Go_director_classes)

## Debugging

```sh
source .dev/venv/bin/activate
./dev.py run
```

Inspect swig generated code.

```sh
( TMPDIR=$(pwd)/build/go CGO_CXXFLAGS="-std=c++11" go run --work main.go )
```

## Implementation

- [ ] Add QML integration test file

### App initialize the C++ runtime - go code

### C++ runtime initialize the qml runtime

### C++ runtime registers the Qt foreign objects

## TODO

- [ ] Try nix for dependencies