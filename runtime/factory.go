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

func (fg *factoryGo) deleteFactoryAbstract() {
	DeleteDirectorFactoryAbstract(fg.FactoryAbstract)
}

func (fg *factoryGo) IsFactoryGo() {}

type overwrittenMethodsOnFactoryAbstract struct {
	fa FactoryAbstract
}

func (om *overwrittenMethodsOnFactoryAbstract) CreateObject() ObjectAbstract {
	fmt.Println("@dd GO CreateObject")
	return NewObjectGo()
}

func NewFactoryGo() Factory {
	om := &overwrittenMethodsOnFactoryAbstract{}
	fa := NewDirectorFactoryAbstract(om)
	om.fa = fa

	fg := &factoryGo{FactoryAbstract: fa}
	return fg
}

// Recommended to be removed if runtime.SetFinalizer is in use.
func DeleteFactoryGo(f Factory) {
	f.deleteFactoryAbstract()
}
