package main

import (
	"encoding/json"
	"fmt"

	"github.com/stefandunca/fobjects/runtime"
)

func main() {
	fmt.Println("@dd GO Starting main")

	f := runtime.NewFactoryGo()
	defer runtime.DeleteFactoryGo(f)

	args := []string{}
	jsonArgs, err := json.Marshal(args)
	if err != nil {
		fmt.Println("Error marshaling arguments:", err)
		return
	}
	r := runtime.NewRuntime(string(jsonArgs))
	defer runtime.DeleteRuntime(r)

	r.Run(f, "??.qml")

	fmt.Println("@dd GO Ending main")
}
