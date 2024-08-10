package runtime

import "fmt"

type Object interface {
	ObjectAbstract
	deleteObjectAbstract()
	IsObjectGo()
}

type objectGo struct {
	ObjectAbstract
}

func (og *objectGo) deleteObjectAbstract() {
	DeleteDirectorObjectAbstract(og.ObjectAbstract)
}

func (og *objectGo) IsObjectGo() {}

type overwrittenMethodsOnObjectAbstract struct {
	ci ObjectAbstract

	stringProperty string
	callback       PropertyChangedCallback
}

func (om *overwrittenMethodsOnObjectAbstract) SetStringProperty(value string) {
	fmt.Println("@dd GO SetStringProperty", value, om.callback)
	om.stringProperty = value
	if om.callback != nil {
		om.callback.Changed()
	}
}

func (om *overwrittenMethodsOnObjectAbstract) GetStringProperty() string {
	fmt.Println("@dd GO GetStringProperty", om.stringProperty)
	return om.stringProperty
}

func (om *overwrittenMethodsOnObjectAbstract) RegisterForStringPropertyChanges(callback PropertyChangedCallback) {
	fmt.Println("@dd GO RegisterForStringPropertyChange", callback)
	om.callback = callback
}

func NewObjectGo() Object {
	om := &overwrittenMethodsOnObjectAbstract{}
	oa := NewDirectorObjectAbstract(om)
	om.ci = oa

	og := &objectGo{ObjectAbstract: oa}
	return og
}

// Recommended to be removed if runtime.SetFinalizer is in use.
func DeleteObjectGo(o Object) {
	o.deleteObjectAbstract()
}
