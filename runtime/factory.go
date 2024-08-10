package runtime

import "fmt"

type Factory interface {
	FactoryAbstract
	deleteFactoryAbstract()
	IsFactoryGo()
}

type factoryGo struct {
	FactoryAbstract
}

func (cigs *factoryGo) deleteFactoryAbstract() {
	DeleteDirectorFactoryAbstract(cigs.FactoryAbstract)
}

func (cigs *factoryGo) IsFactoryGo() {}

type overwrittenMethodsOnFactoryAbstract struct {
	ci FactoryAbstract
}

func (t *overwrittenMethodsOnFactoryAbstract) CreateObject() ObjectAbstract {
	fmt.Println("@dd GO CreateObject")
	return NewObjectGo()
}

func NewFactoryGo() Factory {
	om := &overwrittenMethodsOnFactoryAbstract{}
	ci := NewDirectorFactoryAbstract(om)
	om.ci = ci

	cigs := &factoryGo{FactoryAbstract: ci}
	return cigs
}

// Recommended to be removed if runtime.SetFinalizer is in use.
func DeleteFactoryGo(fbg Factory) {
	fbg.deleteFactoryAbstract()
}
