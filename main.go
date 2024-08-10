package main

import (
	"fmt"

	"github.com/stefandunca/fobjects/runtime"
)

func main() {
	fmt.Println("Starting main")

	f := runtime.NewFactoryGo()
	defer runtime.DeleteFactoryGo(f)

	r := runtime.NewRuntime("[]")
	defer runtime.DeleteRuntime(r)

	r.Run(f)

	fmt.Println("Ending main")
}
