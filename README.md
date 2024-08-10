# fobjects

## Swig

[Running swig with go](https://www.swig.org/Doc4.0/Go.html#Go_running_swig)
[Swig Director Classes](https://www.swig.org/Doc4.0/Go.html#Go_director_classes)

## Debugging

Inspect wig generated code.

```sh
( TMPDIR=$(pwd)/build/go CGO_CXXFLAGS="-std=c++11" go run --work main.go )
```
