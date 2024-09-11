package runtime

import "fmt"

type Project interface {
	ProjectAbstract
	deleteProjectAbstract()
	IsProjectGo()
}

type projectGo struct {
	ProjectAbstract
}

func (og *projectGo) deleteProjectAbstract() {
	DeleteDirectorProjectAbstract(og.ProjectAbstract)
}

func (og *projectGo) IsProjectGo() {}

type overwrittenMethodsOnProjectAbstract struct {
	ci ProjectAbstract
}

func (om *overwrittenMethodsOnProjectAbstract) ComponentComplete() {
	fmt.Println("@dd GO ProjectAbstract ComponentComplete")

	// TODO: introspect children Objects
}

func NewProjectGo() Project {
	om := &overwrittenMethodsOnProjectAbstract{}
	oa := NewDirectorProjectAbstract(om)
	om.ci = oa

	og := &projectGo{ProjectAbstract: oa}
	return og
}

// Recommended to be removed if runtime.SetFinalizer is in use.
func DeleteProjectGo(o Project) {
	o.deleteProjectAbstract()
}
