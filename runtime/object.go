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

func (cigs *objectGo) deleteObjectAbstract() {
	DeleteDirectorObjectAbstract(cigs.ObjectAbstract)
}

func (cigs *objectGo) IsObjectGo() {}

type overwrittenMethodsOnObjectAbstract struct {
	ci ObjectAbstract

	stringProperty string
	callback       PropertyChangedCallback
}

func (t *overwrittenMethodsOnObjectAbstract) SetStringProperty(value string) {
	fmt.Println("@dd GO SetStringProperty", value, t.callback)
	t.stringProperty = value
	if t.callback != nil {
		t.callback.Changed()
	}
}

func (t *overwrittenMethodsOnObjectAbstract) GetStringProperty() string {
	fmt.Println("@dd GO GetStringProperty", t.stringProperty)
	return t.stringProperty
}

func (t *overwrittenMethodsOnObjectAbstract) RegisterForStringPropertyChanges(callback PropertyChangedCallback) {
	fmt.Println("@dd GO RegisterForStringPropertyChange", callback)
	t.callback = callback
}

func NewObjectGo() Object {
	om := &overwrittenMethodsOnObjectAbstract{}
	ci := NewDirectorObjectAbstract(om)
	om.ci = ci

	cigs := &objectGo{ObjectAbstract: ci}
	return cigs
}

// Recommended to be removed if runtime.SetFinalizer is in use.
func DeleteObjectGo(fbg Object) {
	fbg.deleteObjectAbstract()
}
