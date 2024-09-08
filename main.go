package main

import (
	"encoding/json"
	"fmt"
	"os"

	"github.com/stefandunca/fobjects/runtime"
)

func main() {
	fmt.Println("@dd GO Starting main")

	qmlFile := ""
	if len(os.Args) > 1 {
		qmlFile = os.Args[1]
	} else {
		fmt.Println("No arguments provided")
		os.Exit(1)
	}

	f := runtime.NewFactoryGo()
	defer runtime.DeleteFactoryGo(f)

	args := []string{}
	jsonArgs, err := json.Marshal(args)
	if err != nil {
		fmt.Println("Error marshaling arguments:", err)
		os.Exit(2)
	}
	r := runtime.NewRuntime(string(jsonArgs))
	defer runtime.DeleteRuntime(r)

	r.Run(f, qmlFile)

	fmt.Println("@dd GO Ending main")
}
